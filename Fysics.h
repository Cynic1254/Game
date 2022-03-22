#pragma once
#include "Component.h"

#include <utility>

class Fysics :
    public Component
{
public:
  virtual void CollidesWith(Entity& self, Entity& other, std::pair<BoxCollider*, BoxCollider*> colliders) override;
protected:
private:
};

