#include "PlayerController.h"

#include <cassert>

#include "Entity.h"
#include "settings.h"
#include "template.h"
#include "Transform.h"

double PlayerController::yMovement = 0.0;

void PlayerController::Update(Entity& entity)
{
    Transform* transform = entity.GetComponent<Transform>();

    assert(transform != nullptr);

    const double delta = timer.ElapsedSeconds();

    double x = 0.0;

    if (right)
        x += settings::playerSpeed * delta;
    if (left)
        x -= settings::playerSpeed * delta;

    transform->AddPosition({ static_cast<float>(x), 0.0f });

    yMovement = 0;
    yMovement = settings::playerSpeed * delta;
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

    std::cout << lives << std::endl;
  }
}
