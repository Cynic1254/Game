#pragma once

#include "Component.h"

enum class CollisionType;

class Fysics :
  public Component
{
public:
  /// <summary>
  /// entity collided with blocking collider
  /// </summary>
  /// <param name="other"></param>
  /// <param name="collision"></param>
  void CollidesWith(const Entity& self, const Entity& other) const;
};
