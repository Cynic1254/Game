#pragma once

#include "Component.h"
#include "template.h"

#include <vector>

class Entity;

enum class CollisionType {
    none    =   (1 << 0),
    block   =   (1 << 1), 
    hurt    =   (1 << 2)
};

struct Bounds {
  Bounds(Tmpl8::vec2 offset, Tmpl8::vec2 size) : 
      offset(offset), size(size){}

  Tmpl8::vec2 offset;
  Tmpl8::vec2 size;
};

class BoxCollider :
    public Component
{
public:
    BoxCollider(Bounds bounds, CollisionType type) : 
        type(type),
        bounds(bounds)
    {}
    
    static std::vector<std::pair<Entity&, int>> At(Tmpl8::vec2 pos, Bounds bounds);

    CollisionType GetCollisionType() { return type; };
    Bounds GetBounds() { return bounds; };

  protected:
  private:
    CollisionType type = CollisionType::none;
    Bounds bounds;
};
