#include "Wrap.h"

#include <cassert>

#include "Entity.h"
#include "PlayerController.h"
#include "settings.h"
#include "Transform.h"

void Wrap::Update(Entity& entity)
{
    Transform* transform = entity.GetComponent<Transform>();
    assert(transform != nullptr);

    const float yMovement = PlayerController::GetYMovement();

    transform->SetPosition({
      transform->GetPosition().x,
      static_cast<float>(fmod(transform->GetPosition().y - yMovement, settings::tileSize)) - settings::tileSize
    });
}
