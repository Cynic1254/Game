#pragma once
#include "Component.h"

class Wrap :
  public Component
{
public:
  /**
   * \brief makes object seem to move up infinitely
   * \param entity 
   */
  void Update(Entity& entity) override;
};
