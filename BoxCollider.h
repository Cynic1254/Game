#pragma once

#include "Component.h"
#include "template.h"

#include <vector>

class Entity;

enum class CollisionType {
  none = (1 << 0),
  block = (1 << 1),
  hurt = (1 << 2)
};

struct Bounds {
  Bounds(Entity& entity, Tmpl8::vec2 offset, Tmpl8::vec2 size) :
    entity(entity), offset(offset), size(size) {}

  float Top();
  float Bottom();
  float Left();
  float Right();

  Tmpl8::vec2 offset;
  Tmpl8::vec2 size;
private:
  Entity& entity;
};

class BoxCollider :
  public Component
{
public:
  BoxCollider(Bounds bounds, CollisionType type) :
    type(type),
    bounds(bounds)
  {}

  /// <summary>
  /// checks collision at pos
  /// </summary>
  /// <param name="pos"></param>
  /// <param name="bounds"></param>
  /// <returns></returns>
  static std::vector<std::pair<Entity&, int>> At(Tmpl8::vec2 pos, Bounds bounds);
  int At(Entity& entity, Tmpl8::vec2 pos);

  /// <summary>
  /// checks 2 entities against eachother
  /// </summary>
  /// <param name="entityA"></param>
  /// <param name="entityB"></param>
  /// <returns></returns>
  static std::pair<BoxCollider*, BoxCollider*> Collides(Entity& entityA, Entity& entityB);

  CollisionType GetCollisionType() { return type; };
  Bounds GetBounds() { return bounds; };

  virtual void Render(Entity& entity, Tmpl8::Surface& screen) override;

protected:
private:
  CollisionType type = CollisionType::none;
  Bounds bounds;
};
