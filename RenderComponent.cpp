#include "RenderComponent.h"

#include <cassert>

#include "Entity.h"
#include "game.h"
#include "settings.h"
#include "surface.h"
#include "template.h"
#include "Transform.h"

std::multimap<float, RenderObject> RenderComponent::renderQueue = std::multimap<float, RenderObject>();

void RenderComponent::Render(Entity& entity, tmpl8::Surface& screen)
{
  if (isActive)
  {
    Transform* transform = entity.GetComponent<Transform>();
    assert(transform != nullptr);

    RenderObject renderObject(transform->GetPosition(), sprite, &screen);

    renderQueue.insert(std::pair<float, RenderObject>(renderObject.pos.y + sprite.GetHeight(), renderObject));
  }
}

void RenderComponent::RenderAll()
{
  const float playerXPos = tmpl8::Game::Get().GetPlayer().GetComponent<Transform>()->GetPosition().x;
  float cameraOffset;

  if (playerXPos < settings::leftScreenBound + tmpl8::Game::Get().GetScreen()->GetWidth() / 2 - settings::tileSize / 2)
    cameraOffset = 0.0f;
  else if (playerXPos > settings::rightScreenBound - tmpl8::Game::Get().GetScreen()->GetWidth() / 2 + settings::tileSize / 2)
    cameraOffset = settings::rightScreenBound - tmpl8::Game::Get().GetScreen()->GetWidth() + settings::tileSize;
  else
    cameraOffset = playerXPos - tmpl8::Game::Get().GetScreen()->GetWidth() / 2 + settings::tileSize / 2;

  for (auto& r : renderQueue)
  {
    r.second.sprite.Draw(r.second.dst, static_cast<int>(r.second.pos.x - cameraOffset),
                         static_cast<int>(r.second.pos.y));
  }

  renderQueue.clear();
}

void RenderComponent::SetFrame(unsigned int a_Index)
{
  sprite.SetFrame(a_Index);
}

int RenderComponent::GetWidth() const
{
  return sprite.GetWidth();
}

int RenderComponent::GetHeight() const
{
  return sprite.GetHeight();
}

Pixel* RenderComponent::GetBuffer() const
{
  return sprite.GetBuffer();
}

unsigned int RenderComponent::Frames() const
{
  return sprite.Frames();
}
