#include "Entity.h"
#include "Component.h"

#include <iostream>

class BoxCollider;

Entity::~Entity()
{
  for (auto& iter : components)
  {
    delete iter.second;
  }
}

void Entity::Update()
{
  for (auto& c : components)
  {
    if (c.second->GetState())
    {
      c.second->Update(*this);
    }
  }
}

void Entity::Render(Tmpl8::Surface& screen)
{
  for (auto& c : components)
  {
    c.second->Render(*this, screen);
  }
}

void Entity::KeyUp(SDL_Scancode key)
{
  for (auto& c : components)
  {
    c.second->KeyUp(*this, key);
  }
}

void Entity::KeyDown(SDL_Scancode key)
{
  for (auto& c : components)
  {
    c.second->KeyDown(*this, key);
  }
}

void Entity::MouseMove(int x, int y)
{
  for (auto& c : components)
  {
    c.second->MouseMove(*this, x, y);
  }
}

void Entity::MouseUp(int key)
{
  for (auto& c : components)
  {
    c.second->MouseUp(*this, key);
  }
}

void Entity::MouseDown(int key)
{
  for (auto& c : components)
  {
    c.second->MouseDown(*this, key);
  }
}

void Entity::CollidesWith(Entity& entity, std::pair<BoxCollider*, BoxCollider*> colliders)
{
  for (auto& c : components)
  {
    c.second->CollidesWith(*this, entity, colliders);
  }
}

void Entity::Hurt()
{
  for (auto& c : components)
  {
    c.second->Hurt(*this);
  }
}

void Entity::SetActive(bool state)
{
  for (auto& c : components)
  {
    c.second->SetActive(state);
  }
}
