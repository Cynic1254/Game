#pragma once
#include "Component.h"

class Wrap :
  public Component
{
public:
  void Update(Entity& entity) override;
};
