#include "Loop.h"

#include "Transform.h"
#include "PlayerController.h"
#include "Entity.h"

#include "settings.h"

#include <cassert>

void Loop::Update(Entity& entity)
{
    Transform* transform = entity.GetComponent<Transform>();
    assert(transform != nullptr);

    float yMovement = PlayerController::GetYMovement();

    transform->SetPosition({ 0.0f, (float)fmod(transform->GetPosition().y + yMovement, tileSize) });
}
