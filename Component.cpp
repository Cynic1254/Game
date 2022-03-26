#include "Component.h"

#include <utility>

class BoxCollider;

void Component::Update(Entity&)
{
}

void Component::Render(Entity&, tmpl8::Surface&)
{
}

void Component::KeyUp(Entity&, SDL_Scancode)
{
}

void Component::KeyDown(Entity&, SDL_Scancode)
{
}

void Component::MouseMove(Entity&, int, int)
{
}

void Component::MouseUp(Entity&, int)
{
}

void Component::MouseDown(Entity&, int)
{
}

void Component::CollidesWith(Entity& self, Entity& other, std::pair<BoxCollider*, BoxCollider*> colliders)
{
}

void Component::Hurt(Entity& self)
{
}
