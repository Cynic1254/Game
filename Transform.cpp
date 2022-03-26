#include "Transform.h"

#include "BoxCollider.h"

void Transform::SetPosition(const tmpl8::vec2 position)
{
    this->m_position = position;
}

void Transform::AddPosition(const tmpl8::vec2 position)
{
    this->m_position += position;
}

tmpl8::vec2 Transform::GetPosition() const
{
    return m_position;
}
