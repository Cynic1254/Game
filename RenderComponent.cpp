#include "RenderComponent.h"

#include "surface.h"
#include "Transform.h"
#include "Entity.h"
#include "template.h"
#include "game.h"

#include "settings.h"

#include <cassert>

std::multimap<float, RenderObject> RenderComponent::renderQueue = std::multimap<float, RenderObject>();

void RenderComponent::Render(Entity& entity, Tmpl8::Surface& screen)
{
    Transform* transform = entity.GetComponent<Transform>();
    assert(transform != nullptr);

    RenderObject renderObject(transform->GetPosition(), sprite, &screen);

    renderQueue.insert(std::pair<float, RenderObject>(renderObject.pos.y + sprite.GetHeight(), renderObject));
}

void RenderComponent::RenderAll()
{
    float playerXPos = Tmpl8::Game::Get().GetPlayer()->GetComponent<Transform>()->GetPosition().x;
    float cameraOffset;
    if (playerXPos < leftScreenBound + Tmpl8::Game::Get().GetScreen()->GetWidth() / 2 - tileSize / 2)
        cameraOffset = 0.0f;
    else if (playerXPos > rightScreenBound - Tmpl8::Game::Get().GetScreen()->GetWidth() / 2 + tileSize / 2)
        cameraOffset = rightScreenBound - Tmpl8::Game::Get().GetScreen()->GetWidth() + tileSize;
    else
        cameraOffset = playerXPos - Tmpl8::Game::Get().GetScreen()->GetWidth() / 2 + tileSize / 2;

    for (auto& r : renderQueue)
    {
        r.second.sprite.Draw(r.second.dst, (int)r.second.pos.x - cameraOffset, (int)r.second.pos.y);
    }

    renderQueue.clear();
}

void RenderComponent::SetFrame(unsigned int a_Index)
{
    sprite.SetFrame(a_Index);
}

int RenderComponent::GetWidth()
{
    return sprite.GetWidth();
}

int RenderComponent::GetHeight()
{
    return sprite.GetHeight();
}

Pixel* RenderComponent::GetBuffer()
{
    return sprite.GetBuffer();
}

unsigned int RenderComponent::Frames()
{
    return sprite.Frames();
}
