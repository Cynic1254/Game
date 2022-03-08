#include "RenderComponent.h"
#include "surface.h"
#include "Transform.h"
#include "Entity.h"
#include "template.h"
#include "game.h"

#include "settings.h"

#include <cassert>

float screenOffset;

void RenderComponent::Render(Entity& entity, Tmpl8::Surface& screen)
{
    float playerX = Tmpl8::Game::Get().GetPlayer()->GetComponent<Transform>()->GetPosition().x;

    /*if (playerX <= leftScreenBound + Tmpl8::Game::Get().GetScreen()->GetWidth() / 2 - tileSize / 2)
        screenOffset = 0.0f;
    else if (playerX >= rightScreenBound - Tmpl8::Game::Get().GetScreen()->GetWidth() / 2 + tileSize / 2)
        screenOffset = rightScreenBound - Tmpl8::Game::Get().GetScreen()->GetWidth();
    else
        screenOffset = playerX - Tmpl8::Game::Get().GetScreen()->GetWidth() / 2;*/

    if (playerX > leftScreenBound + Tmpl8::Game::Get().GetScreen()->GetWidth() / 2 - tileSize / 2 &&
        playerX < rightScreenBound - Tmpl8::Game::Get().GetScreen()->GetWidth() / 2 + tileSize / 2)
    {
        screenOffset = playerX - Tmpl8::Game::Get().GetScreen()->GetWidth() / 2;
    }

    Transform* transform = entity.GetComponent<Transform>();
    assert(transform != nullptr);

    Tmpl8::vec2 pos = transform->GetPosition();

    sprite.Draw(&screen, (int)(pos.x - screenOffset), (int)pos.y);
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
