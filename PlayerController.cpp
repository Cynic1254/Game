#include "PlayerController.h"

#include "Transform.h"
#include "Entity.h"
#include "template.h"
#include "BoxCollider.h"
#include "RenderComponent.h"
#include "game.h"

#include "settings.h"

#include <cassert>
#include <vector>

double PlayerController::yMovement = 0.0f;

void PlayerController::Update(Entity& entity)
{
    Transform* transform = entity.GetComponent<Transform>();

    assert(transform != nullptr);

    double delta = timer.ElapsedSeconds();

    double x = .0;

    if (right)
        x += PlayerSpeed * delta;
    if (left)
        x -= PlayerSpeed * delta;

    if (!BoxCollider::Collides(entity, Tmpl8::vec2{ 0.0f, (float)(PlayerSpeed * delta) }))
    {
        yMovement = PlayerSpeed * delta;
        std::cout << "moved y" << std::endl;
    }
    if (!BoxCollider::Collides(entity, { (float)x, (float)(PlayerSpeed * delta) }))
    {
        transform->AddPosition({ (float)x, 0.0f });
        std::cout << "moved x" << std::endl;
    }

    std::cout << BoxCollider::Collides(entity, { (float)x, (float)(PlayerSpeed * delta) }) << std::endl;
}

void PlayerController::KeyDown(Entity& entity, SDL_Scancode key)
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

void PlayerController::KeyUp(Entity& entity, SDL_Scancode key)
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
