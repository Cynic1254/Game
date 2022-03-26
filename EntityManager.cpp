#include "EntityManager.h"

#include <cassert>

#include "game.h"
#include "Transform.h"

void EntityManager::Update()
{
}

void EntityManager::Deactivate(const std::vector<Entity*>::const_iterator& iter)
{
  (*iter)->SetActive(false);

  inactive.push(*iter);
  active.erase(iter);
}

void EntityManager::Activate(tmpl8::vec2 pos)
{
  if (!inactive.empty())
  {
    inactive.front()->SetActive(true);
    Transform* transform = inactive.front()->GetComponent<Transform>();
    assert(transform != nullptr);

    transform->SetPosition(pos);

    active.push_back(inactive.front());
    inactive.pop();
  }
  else
  {
    tmpl8::Game::Get().AddObstacle(pos);
  }
}
