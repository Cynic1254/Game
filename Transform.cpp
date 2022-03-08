#include "Transform.h"
#include "BoxCollider.h"
#include "game.h"

void Transform::SetPosition(Tmpl8::vec2 position)
{
    this->position = position;
}

void Transform::AddPosition(Tmpl8::vec2 position)
{
    this->position += position;
}

Tmpl8::vec2 Transform::GetPosition()
{
    return position;
}
