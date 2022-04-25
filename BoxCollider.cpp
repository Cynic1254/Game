#include "BoxCollider.h"

#include <cassert>

#include "game.h"
#include "surface.h"
#include "Transform.h"

CollisionType BoxCollider::Collides(const Entity& entityA, const Entity& entityB) {

  const std::vector<BoxCollider*> collidersA = entityA.GetComponents<BoxCollider>();
  const std::vector<BoxCollider*> collidersB = entityB.GetComponents<BoxCollider>();

  if(collidersA.empty() || collidersB.empty())
    return CollisionType::none;

  CollisionType highestCollision = CollisionType::none;

  for (const auto a : collidersA)
  {
    for (const auto b : collidersB)
    {
      if(a->CollidesWith(*b))
      {
        if(b->type == CollisionType::block)
        {
          return CollisionType::block;
        }
        highestCollision = CollisionType::hurt;
      }
    }
  }

  return highestCollision;
}

bool BoxCollider::CollidesWith(const BoxCollider& collider) const
{
  const tmpl8::vec2 min1 = {bounds.Left(), bounds.Top()};
  const tmpl8::vec2 max1 = {bounds.Right(), bounds.Bottom()};

  const tmpl8::vec2 min2 = {collider.bounds.Left(), collider.bounds.Top()};
  const tmpl8::vec2 max2 = {collider.bounds.Right(), collider.bounds.Bottom()};

  return !(max1.x < min2.x || min1.x > max2.x || max1.y < min2.y || min1.y > max2.y);
}

void BoxCollider::Render(Entity& entity, tmpl8::Surface& screen)
{
  if (tmpl8::Game::Get().IsDebug())
  {
    screen.Box(static_cast<int>(bounds.Left()), static_cast<int>(bounds.Top()), static_cast<int>(bounds.Right()), static_cast<int>(bounds.Bottom()), 0x0);
  }
}

float Bounds::Top() const
{
  const Transform* transform = entity.GetComponent<Transform>();
  assert(transform != nullptr);
  return transform->GetPosition().y + offset.y;
}

float Bounds::Bottom() const
{
  const Transform* transform = entity.GetComponent<Transform>();
  assert(transform != nullptr);
  return transform->GetPosition().y + offset.y + size.y;
}

float Bounds::Left() const
{
  const Transform* transform = entity.GetComponent<Transform>();
  assert(transform != nullptr);
  return transform->GetPosition().x + offset.x;
}

float Bounds::Right() const
{
  const Transform* transform = entity.GetComponent<Transform>();
  assert(transform != nullptr);
  return transform->GetPosition().x + offset.x + size.x;
}
