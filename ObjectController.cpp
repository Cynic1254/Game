#include "ObjectController.h"

#include "Transform.h"
#include "PlayerController.h"
#include "Entity.h"
#include "game.h"
#include "surface.h"
#include "RenderComponent.h"

#include <cassert>

void ObjectController::Update(Entity& entity)
{
  Transform* transform = entity.GetComponent<Transform>();
  RenderComponent* renderComponent = entity.GetComponent<RenderComponent>();
  assert(transform != nullptr && renderComponent != nullptr);

  transform->AddPosition({ 0.0f, (float)-PlayerController::GetYMovement() });

  if (transform->GetPosition().y < -renderComponent->GetHeight())
  {
    entity.SetActive(false);
  }
}
