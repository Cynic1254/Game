#include "Fysics.h"

#include "Transform.h"
#include "Entity.h"
#include "BoxCollider.h"
#include "game.h"

#include <cassert>
#include <vector>

bool Fysics::Move(Tmpl8::vec2 move, Entity& entity)
{
    Transform* transform = entity.GetComponent<Transform>();

    assert(transform != nullptr);

    if (!BoxCollider::Collides(entity, move))
    {
        transform->AddPosition(move);
        return true;
    }
    if (!BoxCollider::Collides(entity, { move.x, 0.0f }))
    {
        transform->AddPosition({ move.x, 0.0f });
        return true;
    }
    if (!BoxCollider::Collides(entity, { 0.0f, move.y }))
    {
        transform->AddPosition({ 0.0f, move.y });
        return true;
    }

    return false;
}
