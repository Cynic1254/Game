#pragma once
#include "Component.h"

class Entity;

class ObjectController :
  public Component
{
public:
  /**
   * \brief moves object upwards and disables self if above the screen
   * \param entity 
   */
  void Update(Entity& entity) override;
  void SetActive(Entity& entity, bool state) override;
};

