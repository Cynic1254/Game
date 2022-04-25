#pragma once

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
  static CollisionType Collides(const Entity& entityA, const Entity& entityB);

  /**
   * \brief checks if collider collides
   * \param collider collider to check against
   * \return 
   */
  bool CollidesWith(const BoxCollider& collider) const;

  CollisionType GetCollisionType() const { return type; }
  Bounds GetBounds() { return bounds; }

  /**
   * \brief debug function, renders colliders
   * \param entity 
   * \param screen 
   */
  void Render(Entity& entity, tmpl8::Surface& screen) override;

private:
  CollisionType type = CollisionType::none;
  Bounds bounds;
};
