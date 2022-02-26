#include "RenderComponent.h"
#include "surface.h"
#include "Transform.h"
#include "Entity.h"
#include "template.h"
#include "game.h"

void RenderComponent::Render(Entity& entity, Tmpl8::Surface& screen)
{
    Transform* transform = entity.GetComponent<Transform>();
    if (transform == nullptr)
        return;

    Tmpl8::vec2 pos = transform->GetPosition();
    Tmpl8::vec2 screenOffset = transform->GetScreenPosition();
    screenOffset -= {(float)(Tmpl8::Game::Get().GetScreen()->GetWidth() / 2) - (float)(sprite.GetWidth() / 2), (float)(Tmpl8::Game::Get().GetScreen()->GetHeight() / 2) - (float)(sprite.GetHeight() / 2)};

    sprite.Draw(&screen, (int)(pos.x - screenOffset.x), (int)(pos.y - screenOffset.y));
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
