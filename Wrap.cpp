#include "Wrap.h"

#include "Transform.h"
#include "PlayerController.h"
#include "Entity.h"

#include "settings.h"

#include <cassert>

void Wrap::Update(Entity& entity)
{
    Transform* transform = entity.GetComponent<Transform>();
    assert(transform != nullptr);

    float yMovement = PlayerController::GetYMovement();

    transform->SetPosition({ transform->GetPosition().x, (float)fmod(transform->GetPosition().y - yMovement, settings::tileSize) - settings::tileSize});
}
