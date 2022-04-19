#include "PlayerController.h"

#include <cassert>

#include "Entity.h"
#include "settings.h"
#include "template.h"
#include "Transform.h"
#include "game.h"
#include "RenderComponent.h"

float PlayerController::yMovement = 0.0;
bool PlayerController::isActive = true;
int PlayerController::lives = settings::playerLives;

void PlayerController::Update(Entity& entity)
{
  if(!isActive)
    return;

  Transform* transform = entity.GetComponent<Transform>();
  RenderComponent* renderComponent = entity.GetComponent<RenderComponent>();

  assert(transform != nullptr && renderComponent != nullptr);

  const double delta = timer.ElapsedSeconds();

  double x = 0.0;
  double y = 0.0;

  if (right)
    x += settings::playerSpeed * delta;
  if (left)
    x -= settings::playerSpeed * delta;

  if (x == 0.0)
  {
    renderComponent->SetFrame(2);
  }
  if (x < 0.0)
  {
    renderComponent->SetFrame(4);
  }
  if (x > 0.0)
  {
    renderComponent->SetFrame(3);
  }

  transform->AddPosition({static_cast<float>(x), static_cast<float>(y)});

  if (transform->GetPosition().y > ScreenHeight - settings::tileSize)
  {
    transform->SetPosition({transform->GetPosition().x, ScreenHeight - settings::tileSize});
  }
  if (transform->GetPosition().y < 0)
  {
    transform->SetPosition({transform->GetPosition().x, 0.0f});
  }

  yMovement = static_cast<float>(settings::playerSpeed * delta);
  if (invincibility > 0)
  {
    invincibility -= delta;
  }
}

void PlayerController::KeyDown(Entity& entity, const SDL_Scancode key)
{
  switch (key)
  {
  case SDL_SCANCODE_A:
  case SDL_SCANCODE_LEFT:
    left = true;
    break;

  case SDL_SCANCODE_D:
  case SDL_SCANCODE_RIGHT:
    right = true;
    break;

  case SDL_SCANCODE_W:
  case SDL_SCANCODE_UP:
    up = true;
    break;

  case SDL_SCANCODE_S:
  case SDL_SCANCODE_DOWN:
    down = true;
    break;

  default:
    break;
  }
}

void PlayerController::KeyUp(Entity& entity, const SDL_Scancode key)
{
  switch (key)
  {
  case SDL_SCANCODE_A:
  case SDL_SCANCODE_LEFT:
    left = false;
    break;

  case SDL_SCANCODE_D:
  case SDL_SCANCODE_RIGHT:
    right = false;
    break;

  case SDL_SCANCODE_W:
  case SDL_SCANCODE_UP:
    up = false;
    break;

  case SDL_SCANCODE_S:
  case SDL_SCANCODE_DOWN:
    down = false;
    break;

  default:
    break;
  }
}

void PlayerController::Hurt(Entity& entity)
{
  if (invincibility < 0)
  {
    --lives;
    invincibility = settings::invincibilityCooldown;

    if (lives <= 0)
    {
      tmpl8::Game::Get().EndGame();
    }
  }
}

float PlayerController::GetYMovement()
{
  if(!isActive)
    return 0.0;

  return yMovement;
}

void PlayerController::SetActive(Entity& entity, bool state)
{
  lives = settings::playerLives;
  isActive = state;
}
