#pragma once
#include "Component.h"

class Entity;

class ObjectController :
  public Component
{
public:
  void Update(Entity& entity) override;
  void SetActive(Entity& entity, bool state) override;
};

