#pragma once
#include "Component.h"

class Entity;

class ObjectController :
    public Component
{
public:
  virtual void Update(Entity& entity) override;
  virtual void SetActive(Entity& entity, bool state) override;
protected:
private:
};

