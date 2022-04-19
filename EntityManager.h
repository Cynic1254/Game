#pragma once

#include <queue>
#include <vector>

#include "Entity.h"

namespace tmpl8
{
  class vec2;
}

class EntityManager
{
public:
  EntityManager(std::vector<Entity*>& entities)
    : active(entities)
  {}

  ~EntityManager()
  {
    while (!inactive.empty())
    {
      delete inactive.front();
      inactive.pop();
    }
  }

  EntityManager(EntityManager&) = delete;
  EntityManager(EntityManager&&) = delete;

  EntityManager& operator=(EntityManager&) = delete;
  EntityManager& operator=(EntityManager&&) = delete;

  void Update();

  void Deactivate(Entity& e);
  void Activate(tmpl8::vec2 pos);

  void SetActive(bool state) { isActive = state; }
protected:
private:
  std::vector<Entity*>& active;
  std::queue<Entity*> inactive;

  float spawn_timer = 1.0f;

  bool isActive = true;
};
