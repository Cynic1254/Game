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

  void Deactivate(const std::vector<Entity*>::const_iterator& iter);
  void Activate(tmpl8::vec2 pos);

protected:
private:
  std::vector<Entity*>& active;
  std::queue<Entity*> inactive;
};
