#include "BoxCollider.h"

#include "Transform.h"
#include "game.h"
#include "surface.h"

#include <cassert>

std::vector<std::pair<Entity&, int>> BoxCollider::At(Tmpl8::vec2 pos, Bounds bounds) {
  const std::vector<Entity*>& entities = Tmpl8::Game::Get().GetEntities();

  std::vector<std::pair<Entity&, int>> returnValue;

  {
    Entity& player = Tmpl8::Game::Get().GetPlayer();
    Transform* transform = player.GetComponent<Transform>();
    std::vector<BoxCollider*> boxcollider = player.GetComponents<BoxCollider>();

    assert(transform != nullptr || boxcollider.size() != 0);

    Tmpl8::vec2 pos = transform->GetPosition();

    int collisions = 0;

    for (auto c : boxcollider) {

      Bounds bounds = c->GetBounds();

      Tmpl8::vec2 min = pos + bounds.offset;
      Tmpl8::vec2 max = pos + bounds.offset + bounds.size;

      if (pos.x > min.x && pos.y > min.y && pos.x < max.x && pos.y < max.y) {
        collisions = collisions | (int)c->GetCollisionType();
      }
    }

    if (collisions != 0) {
      returnValue.push_back({ player, collisions });
    }
  }

  for (auto e : entities) {
    Transform* transform = e->GetComponent<Transform>();
    std::vector<BoxCollider*> boxcollider = e->GetComponents<BoxCollider>();
    if (transform == nullptr || boxcollider.size() == 0)
      continue;

    Tmpl8::vec2 pos = transform->GetPosition();

    int collisions = 0;

    for (auto c : boxcollider) {

      Bounds bounds = c->GetBounds();

      Tmpl8::vec2 min = pos + bounds.offset;
      Tmpl8::vec2 max = pos + bounds.offset + bounds.size;

      if (pos.x > min.x && pos.y > min.y && pos.x < max.x && pos.y < max.y) {
        collisions = collisions | (int)c->GetCollisionType();
      }
    }

    if (collisions != 0) {
      returnValue.push_back({ *e, collisions });
    }
  }

  return returnValue;
}

int BoxCollider::At(Entity& entity, Tmpl8::vec2 pos)
{
  std::vector<std::pair<Entity&, int>> collisions = At(pos, bounds);

  int returnValue = 0;

  for (auto& i = collisions.end(); i > collisions.begin(); i--)
  {
    if (&i->first != &entity)
    {
      returnValue = returnValue | i->second;
    }
  }

  return returnValue;
}

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
  screen.Box(bounds.Left(), bounds.Top(), bounds.Right(), bounds.Bottom(), 0x0);
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
