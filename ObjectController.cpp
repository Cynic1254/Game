#include "ObjectController.h"

#include <cassert>

#include "Entity.h"
#include "PlayerController.h"
#include "RenderComponent.h"
#include "Transform.h"

void ObjectController::Update(Entity& entity)
{
  Transform* transform = entity.GetComponent<Transform>();
  RenderComponent* renderComponent = entity.GetComponent<RenderComponent>();
  assert(transform != nullptr && renderComponent != nullptr);

  transform->AddPosition({ 0.0f, static_cast<float>(-PlayerController::GetYMovement()) });

  if (transform->GetPosition().y < -renderComponent->GetHeight())
  {
    entity.SetActive(false);
  }
}
