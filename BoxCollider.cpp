#include "BoxCollider.h"

#include "Transform.h"
#include "game.h"

class Entity;

std::vector<std::pair<Entity &, int>> BoxCollider::At(Tmpl8::vec2 pos, Bounds bounds) {
  const std::vector<Entity *>& entities = Tmpl8::Game::Get().GetEntities();

  std::vector<std::pair<Entity &, int>> returnValue;

  for (auto e : entities) {
    Transform* transform = e->GetComponent<Transform>();
    std::vector<BoxCollider *> boxcollider = e->GetComponents<BoxCollider>();
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
      returnValue.push_back({*e, collisions});
    }
  }

  return returnValue;
}
