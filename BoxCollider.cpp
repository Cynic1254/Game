#include "BoxCollider.h"

#include "Transform.h"
#include "game.h"
#include "surface.h"

#include <cassert>

std::pair<BoxCollider*, BoxCollider*> BoxCollider::Collides(Entity& entityA, Entity& entityB) {
  Transform* transformA = entityA.GetComponent<Transform>();
  Transform* transformB = entityB.GetComponent<Transform>();

  assert(transformA != nullptr && transformB != nullptr);

  std::vector<BoxCollider*> collidersA = entityA.GetComponents<BoxCollider>();
  std::vector<BoxCollider*> collidersB = entityB.GetComponents<BoxCollider>();

  if (collidersA.size() == 0 || collidersB.size() == 0)
    return { nullptr , nullptr};

  for (auto cA : collidersA)
  {
    for (auto cB : collidersB)
    {
      Tmpl8::vec2 minA = transformA->GetPosition() + cA->bounds.offset;
      Tmpl8::vec2 minB = transformB->GetPosition() + cB->bounds.offset;

      Tmpl8::vec2 maxA = transformA->GetPosition() + cA->bounds.offset + cA->bounds.size;
      Tmpl8::vec2 maxB = transformB->GetPosition() + cB->bounds.offset + cB->bounds.size;

      if (minA.x < maxB.x && maxA.x > minB.x && minA.y < maxB.y && maxA.y > minB.y)
        return { cA, cB };
    }
  }

  return { nullptr , nullptr };
}

void BoxCollider::Render(Entity& entity, Tmpl8::Surface& screen)
{
  if (Tmpl8::Game::Get().IsDebug())
  {
    screen.Box(bounds.Left(), bounds.Top(), bounds.Right(), bounds.Bottom(), 0x0);
  }
}

float Bounds::Top()
{
  Transform* transform = entity.GetComponent<Transform>();
  assert(transform != nullptr);
  return transform->GetPosition().y + offset.y;
}

float Bounds::Bottom()
{
  Transform* transform = entity.GetComponent<Transform>();
  assert(transform != nullptr);
  return transform->GetPosition().y + offset.y + size.y;
}

float Bounds::Left()
{
  Transform* transform = entity.GetComponent<Transform>();
  assert(transform != nullptr);
  return transform->GetPosition().x + offset.x;
}

float Bounds::Right()
{
  Transform* transform = entity.GetComponent<Transform>();
  assert(transform != nullptr);
  return transform->GetPosition().x + offset.x + size.x;
}
