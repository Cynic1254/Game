#include "Transform.h"
#include "BoxCollider.h"
#include "game.h"

Tmpl8::vec2 Transform::screenPosition = { 0.0f };

void Transform::SetPosition(Tmpl8::vec2 position)
{
    this->position = position;
}

void Transform::AddPosition(Tmpl8::vec2 position)
{
    this->position += position;
}

bool Transform::CollisionAdd(Entity& entity, Tmpl8::vec2 position)
{
    std::vector<BoxCollider*> entityCollider = entity.GetComponents<BoxCollider>();
    if (entityCollider.size() == 0)
        return true;

    const std::vector<Entity*>& entities = Tmpl8::Game::Get().GetEntities();

    bool moved = false;
    bool collides = false;
    bool collidesHorizontal = false;
    bool collidesVertical = false;
    bool collidesDiagonal = false;

    for (int i = 0; i < entities.size(); i++)
    {
        if (entities[i] != &entity)
        {
            std::vector<BoxCollider*> collider = entities[i]->GetComponents<BoxCollider>();
            for (int j = 0; j < collider.size(); j++)
            {
                if (collider[j]->GetType() == CollisionType::block)
                {
                    for (int k = 0; k < entityCollider.size(); k++)
                    {
                        if (!collidesDiagonal)
                            collidesDiagonal = entityCollider[k]->CollidesAt(this->position + position, *collider[j]);
                        if (!collidesHorizontal)
                            collidesHorizontal = entityCollider[k]->CollidesAt({ this->position.x + position.x, this->position.y }, *collider[j]);
                        if (!collidesVertical)
                            collidesVertical = entityCollider[k]->CollidesAt({ this->position.x, this->position.y + position.y }, *collider[j]);
                    }
                }
            }
        }
    }

    if (!collidesDiagonal)
    {
        AddPosition(position);
        moved = true;
    }
    else if (!collidesHorizontal)
    {
        AddPosition({ position.x, 0.0f });
        moved = true;
    }
    else if (!collidesVertical)
    {
        AddPosition({ 0.0f, position.y });
        moved = true;
    }

    return moved;
}

Tmpl8::vec2 Transform::GetPosition()
{
    return position;
}

Tmpl8::vec2 Transform::GetScreenPosition()
{
    return screenPosition;
}

void Transform::SetScreenPosition(Tmpl8::vec2 screenPosition)
{
    Transform::screenPosition = screenPosition;
}

void Transform::AddScreenPosition(Tmpl8::vec2 screenPosition)
{
    Transform::screenPosition += screenPosition;
}
