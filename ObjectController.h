#pragma once
#include "Component.h"

class Entity;

class ObjectController :
    public Component
{
public:
  virtual void Update(Entity& entity) override;
protected:
private:
};

