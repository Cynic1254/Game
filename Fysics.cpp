#include "Fysics.h"

#include "Entity.h"
#include "BoxCollider.h"
#include "Transform.h"

#include <vector>
#include <cassert>
#include <math.h>

void Fysics::CollidesWith(Entity& self, Entity& other, std::pair<BoxCollider*, BoxCollider*> colliders)
{
  Transform* transformSelf = self.GetComponent<Transform>();
  Transform* transformOther = other.GetComponent<Transform>();

  assert(transformSelf != nullptr && transformOther != nullptr);

  Bounds boundsSelf = colliders.first->GetBounds();
  Bounds boundsOther = colliders.second->GetBounds();

  Tmpl8::vec2 delta = (transformSelf->GetPosition() + boundsSelf.offset + boundsSelf.size / 2) - (transformOther->GetPosition() + boundsOther.offset + boundsOther.size / 2);

  Tmpl8::vec2 absDelta = { abs(delta.x), abs(delta.y) };

  if (absDelta.y < absDelta.x)
  {
    if (delta.x < 0)
    {
      transformSelf->SetPosition({boundsOther.Left() - boundsSelf.size.x - boundsSelf.offset.x, transformSelf->GetPosition().y});
    }
    else
    {
      transformSelf->SetPosition({ boundsOther.Right() - boundsSelf.offset.x, transformSelf->GetPosition().y });
    }
  }
  else
  {
    if (delta.y < 0)
    {
      transformSelf->SetPosition({ transformSelf->GetPosition().x, boundsOther.Top() - boundsSelf.size.y - boundsSelf.offset.y });
    }
    else
    {
      transformSelf->SetPosition({ transformSelf->GetPosition().x, boundsOther.Bottom() - boundsSelf.offset.y});
    }
  }
}
