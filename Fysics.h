#pragma once
#include <utility>

#include "Component.h"

class Fysics :
  public Component
{
public:
  /// <summary>
  /// entity collided with blocking collider
  /// </summary>
  /// <param name="self"></param>
  /// <param name="other"></param>
  /// <param name="colliders"></param>
  void CollidesWith(Entity& self, Entity& other, std::pair<BoxCollider*, BoxCollider*> colliders) override;
};
