#include "PlayerController.h"

#include <cassert>

#include "Entity.h"
#include "settings.h"
#include "template.h"
#include "Transform.h"
#include "game.h"
#include "Menu.h"
#include "RenderComponent.h"

float PlayerController::yMovement = 0.0;
bool PlayerController::isActive = true;
int PlayerController::lives = settings::playerLives;
double PlayerController::score = 0;

PlayerController::PlayerController() :
  timer(Timer::Get())
{
  hurt = new AudioPlayer("assets/sounds/minecraft oof.wav");
  death = new AudioPlayer("assets/sounds/roblox oof.wav");
}

void PlayerController::Update(Entity& entity)
{
  if (!isActive)
    return;

  Transform* transform = entity.GetComponent<Transform>();
  RenderComponent* renderComponent = entity.GetComponent<RenderComponent>();

  assert(transform != nullptr && renderComponent != nullptr);

  const double delta = timer.ElapsedSeconds();

  double x = 0.0;
  if (controllerAxis == 0.0)
  {
    if (right)
      x += settings::playerSpeed * delta;
    if (left)
      x -= settings::playerSpeed * delta;
  }
  else
  {
    x = controllerAxis * settings::playerSpeed * delta;
  }

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

  transform->AddPosition({ static_cast<float>(x), 0.0f });

  yMovement = static_cast<float>(settings::playerSpeed * delta);
  if (invincibility > 0)
  {
    invincibility -= delta;
  }

  score += timer.ElapsedSeconds();
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
      death->PlaySound();
      tmpl8::Game::Get().EndGame();
      tmpl8::Game::Get().GetMenu()->SetState(3);
    }
    else
    {
      hurt->PlaySound();
    }
  }
}

float PlayerController::GetYMovement()
{
  if (!isActive)
    return 0.0;

  return yMovement;
}

void PlayerController::SetActive(Entity& entity, bool state)
{
  if (state)
  {
    lives = settings::playerLives;
    score = 0.0;
  }
  isActive = state;
}

void PlayerController::JoystickMove(Uint8 axis, Sint16 value)
{
  switch (axis)
  {
  case SDL_CONTROLLER_AXIS_LEFTX:
    controllerAxis = value / 32767.0;
    break;
  default:
    break;
  }
}