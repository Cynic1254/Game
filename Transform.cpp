#include "Transform.h"

#include "BoxCollider.h"

void Transform::SetPosition(const tmpl8::vec2 position)
{
    this->position_ = position;
}

void Transform::AddPosition(const tmpl8::vec2 position)
{
    this->position_ += position;
}

tmpl8::vec2 Transform::GetPosition() const
{
    return position_;
}
