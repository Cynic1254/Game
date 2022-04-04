#include "EntityManager.h"

#include <cassert>

#include "game.h"
#include "settings.h"
#include "template.h"
#include "Timer.h"
#include "Transform.h"

void EntityManager::Update()
{
  if (!isActive)
    return;

  spawn_timer -= Timer::Get().ElapsedSeconds();

  if (spawn_timer < 0.0)
  {
    Activate({static_cast<float>(IRand(1000)), ScreenHeight + settings::tileSize});

    spawn_timer = 1.0;
  }
}

void EntityManager::Deactivate(Entity& e)
{
  e.SetActive(false);

  const auto iter = std::find(active.begin(), active.end(), &e);

  inactive.push(*iter);
  active.erase(iter);
}

void EntityManager::Activate(const tmpl8::vec2 pos)
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
