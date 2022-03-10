#include "BoxCollider.h"

#include "Transform.h"
#include "surface.h"
#include "game.h"

#include <cassert>
#include <vector>

void BoxCollider::Update(Entity& entity)
{
    Transform* transformComponent = entity.GetComponent<Transform>();
    assert(transformComponent != nullptr);

    bounds.min = transformComponent->GetPosition() + bounds.offset;
    bounds.max = transformComponent->GetPosition() + bounds.size + bounds.offset;
}

bool BoxCollider::CollidesAt(Tmpl8::vec2 pos, BoxCollider& b)
{
    Bounds a(pos + bounds.offset, Tmpl8::vec2{ pos.x + bounds.size.x, pos.y + bounds.size.y } + bounds.offset);
    return  a.min.x < b.bounds.max.x &&
            a.max.x > b.bounds.min.x &&
            a.min.y < b.bounds.max.y &&
            a.max.y > b.bounds.min.y;
}

bool BoxCollider::Collides(BoxCollider& b)
{
    BoxCollider& a = *this;
    return  a.bounds.min.x < b.bounds.max.x &&
            a.bounds.max.x > b.bounds.min.x &&
            a.bounds.min.y < b.bounds.max.y &&
            a.bounds.max.y > b.bounds.min.y;
}

bool BoxCollider::Collides(Entity& entity, Tmpl8::vec2 pos)
{
    std::vector<BoxCollider*> colliders;
    std::vector<BoxCollider*> entityColliders = entity.GetComponents<BoxCollider>();

    if (entityColliders.size() == 0)
        return false;

    if (&entity != Tmpl8::Game::Get().GetPlayer())
    {
        std::vector<BoxCollider*> playerColliders = Tmpl8::Game::Get().GetPlayer()->GetComponents<BoxCollider>();
        colliders.insert(std::end(colliders),
            std::begin(playerColliders),
            std::end(playerColliders));
    }

    std::vector<Entity*> entities = Tmpl8::Game::Get().GetEntities();

    for (auto& e : entities)
    {
        if (e != &entity)
        {
            std::vector<BoxCollider*> eColliders = e->GetComponents<BoxCollider>();
            colliders.insert(std::end(colliders),
                std::begin(eColliders),
                std::end(eColliders));
        }
    }

    if (colliders.size() == 0)
        return false;

    for (auto& c : entityColliders)
    {
        for (auto& e : colliders)
        {
            if (c->CollidesAt(pos, *e))
                return true;
        }
    }

    return false;
}

void BoxCollider::Render(Entity& entity, Tmpl8::Surface& dst)
{
    dst.Box(bounds.min.x, bounds.min.y, bounds.max.x, bounds.max.y, 0x000000);
}

bool BoxCollider::Collides(BoxCollider& a, BoxCollider& b)
{
    return  a.bounds.min.x < b.bounds.max.x && 
            a.bounds.max.x > b.bounds.min.x &&
            a.bounds.min.y < b.bounds.max.y && 
            a.bounds.max.y > b.bounds.min.y;
}
