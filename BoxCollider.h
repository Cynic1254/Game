#pragma once

#include <vector>

#include "Component.h"
#include "template.h"

class Entity;

enum class CollisionType {
  none,
  block,
  hurt
};

struct Bounds {
  Bounds(Entity& entity, tmpl8::vec2 offset, tmpl8::vec2 size) :
    offset(offset), size(size), entity(entity) {}

  float Top() const;
  float Bottom() const;
  float Left() const;
  float Right() const;

  tmpl8::vec2 offset;
  tmpl8::vec2 size;
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
  /// checks 2 entities against each other
  /// </summary>
  /// <param name="entityA"></param>
  /// <param name="entityB"></param>
  /// <returns></returns>
  static std::pair<BoxCollider*, BoxCollider*> Collides(const Entity& entityA, const Entity& entityB);

  CollisionType GetCollisionType() const { return type; }
  Bounds GetBounds() { return bounds; }

  virtual void Render(Entity& entity, tmpl8::Surface& screen) override;

protected:
private:
  CollisionType type = CollisionType::none;
  Bounds bounds;
};
