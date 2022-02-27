#include "PlayerController.h"
#include "Transform.h"
#include "Entity.h"
#include "template.h"
#include "BoxCollider.h"
#include "RenderComponent.h"

#include <cassert>

constexpr double speed = 60;
constexpr float leftBound = 0;
constexpr float rightBound = 1000;

void PlayerController::Update(Entity& entity)
{
    Transform* transform = entity.GetComponent<Transform>();
    RenderComponent* renderComponent = entity.GetComponent<RenderComponent>();
    
    assert(transform != nullptr || renderComponent != nullptr);

    double delta = timer.ElapsedSeconds();

    double x = .0, y = .0;

    if (right)
        x += speed * delta;
    if (left)
        x -= speed * delta;
    if (down)
        y += speed * delta;
    if (up)
        y -= speed * delta;

    y += speed * delta;

    if ((transform->GetPosition().x < leftBound && x < 0.0) || (transform->GetPosition().x > rightBound && x > 0.0))
        x = 0.0;

    transform->CollisionAdd(entity, { (float)x, (float)y });
    if (transform->GetPosition().x <= leftBound + (ScreenWidth / 2) - renderComponent->GetWidth() / 2 ||
        transform->GetPosition().x >= rightBound - (ScreenWidth / 2) + renderComponent->GetWidth() / 2)
        transform->SetScreenPosition({transform->GetScreenPosition().x, transform->GetPosition().y });
    else
        transform->SetScreenPosition(transform->GetPosition());
}

void PlayerController::KeyDown(Entity& entity, SDL_Scancode key)
{
    switch (key)
    {
    case SDL_SCANCODE_W:
    case SDL_SCANCODE_UP:
        up = true;
        break;

    case SDL_SCANCODE_A:
    case SDL_SCANCODE_LEFT:
        left = true;
        break;

    case SDL_SCANCODE_S:
    case SDL_SCANCODE_DOWN:
        down = true;
        break;

    case SDL_SCANCODE_D:
    case SDL_SCANCODE_RIGHT:
        right = true;
        break;

    default:
        break;
    }
}

void PlayerController::KeyUp(Entity& entity, SDL_Scancode key)
{
    switch (key)
    {
    case SDL_SCANCODE_W:
    case SDL_SCANCODE_UP:
        up = false;
        break;

    case SDL_SCANCODE_A:
    case SDL_SCANCODE_LEFT:
        left = false;
        break;

    case SDL_SCANCODE_S:
    case SDL_SCANCODE_DOWN:
        down = false;
        break;

    case SDL_SCANCODE_D:
    case SDL_SCANCODE_RIGHT:
        right = false;
        break;

    default:
        break;
    }
}
