#include "BoxCollider.h"
#include "Transform.h"
#include "surface.h"

void BoxCollider::Update(Entity& entity)
{
    Transform* transformComponent = entity.GetComponent<Transform>();
    if (transformComponent == nullptr)
        return;

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

bool BoxCollider::Collides(BoxCollider& a, BoxCollider& b)
{
    return  a.bounds.min.x < b.bounds.max.x && 
            a.bounds.max.x > b.bounds.min.x &&
            a.bounds.min.y < b.bounds.max.y && 
            a.bounds.max.y > b.bounds.min.y;
}
