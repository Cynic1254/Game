#include "ObjectController.h"

#include <cassert>

#include "Entity.h"
#include "EntityManager.h"
#include "PlayerController.h"
#include "RenderComponent.h"
#include "Transform.h"
#include "game.h"

void ObjectController::Update(Entity& entity)
{
  Transform* transform = entity.GetComponent<Transform>();
  const RenderComponent* renderComponent = entity.GetComponent<RenderComponent>();
  assert(transform != nullptr && renderComponent != nullptr);

  transform->AddPosition({ 0.0f, static_cast<float>(-PlayerController::GetYMovement()) });

  if (transform->GetPosition().y < static_cast<float>(-renderComponent->GetHeight()))
  {
    entity.SetActive(false);
  }
}

void ObjectController::SetActive(Entity& entity, bool state)
{
  if (!state && isActive)
  {
    Component::SetActive(entity, state);
    tmpl8::Game::Get().GetEntityManager().Deactivate(entity);
  }
  else if (state)
  {
    Component::SetActive(entity, state);
  }
}
