#include "BoxCollider.h"

#include <cassert>

#include "game.h"
#include "surface.h"
#include "Transform.h"

std::pair<BoxCollider*, BoxCollider*> BoxCollider::Collides(const Entity& entityA, const Entity& entityB) {
  Transform* transformA = entityA.GetComponent<Transform>();
  Transform* transformB = entityB.GetComponent<Transform>();

  assert(transformA != nullptr && transformB != nullptr);

  const std::vector<BoxCollider*> collidersA = entityA.GetComponents<BoxCollider>();
  const std::vector<BoxCollider*> collidersB = entityB.GetComponents<BoxCollider>();

  if (collidersA.empty() || collidersB.empty())
    return { nullptr , nullptr};

  for (auto cA : collidersA)
  {
    for (auto cB : collidersB)
    {
      const tmpl8::vec2 minA = transformA->GetPosition() + cA->bounds.offset;
      const tmpl8::vec2 minB = transformB->GetPosition() + cB->bounds.offset;

      const tmpl8::vec2 maxA = transformA->GetPosition() + cA->bounds.offset + cA->bounds.size;
      const tmpl8::vec2 maxB = transformB->GetPosition() + cB->bounds.offset + cB->bounds.size;

      if (minA.x < maxB.x && maxA.x > minB.x && minA.y < maxB.y && maxA.y > minB.y)
        return { cA, cB };
    }
  }

  return { nullptr , nullptr };
}

void BoxCollider::Render(Entity& entity, tmpl8::Surface& screen)
{
  if (tmpl8::Game::Get().IsDebug())
  {
    screen.Box(bounds.Left(), bounds.Top(), bounds.Right(), bounds.Bottom(), 0x0);
  }
}

float Bounds::Top() const
{
  Transform* transform = entity.GetComponent<Transform>();
  assert(transform != nullptr);
  return transform->GetPosition().y + offset.y;
}

float Bounds::Bottom() const
{
  Transform* transform = entity.GetComponent<Transform>();
  assert(transform != nullptr);
  return transform->GetPosition().y + offset.y + size.y;
}

float Bounds::Left() const
{
  Transform* transform = entity.GetComponent<Transform>();
  assert(transform != nullptr);
  return transform->GetPosition().x + offset.x;
}

float Bounds::Right() const
{
  Transform* transform = entity.GetComponent<Transform>();
  assert(transform != nullptr);
  return transform->GetPosition().x + offset.x + size.x;
}
