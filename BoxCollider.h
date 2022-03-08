#pragma once

#include "Component.h"
#include "template.h"
#include "Entity.h"

enum class CollisionType {
    none    =   0,
    block   =   1,
    hurt    =   2
};

struct Bounds {
    Bounds() : min(0.0f), max(0.0f), size(0.0f) {}
    Bounds(Tmpl8::vec2 v) : min(v), max(v), offset(0.0f), size(0.0f) {}
    Bounds(Tmpl8::vec2 min, Tmpl8::vec2 max) : min(min), max(max), offset(0.0f) { size = max - min; }
    Bounds(Tmpl8::vec2 min, Tmpl8::vec2 max, Tmpl8::vec2 offset) : min(min), max(max), offset(offset) { size = max - min; }

    union {
        struct {
            Tmpl8::vec2 min, max;
        };
        Tmpl8::vec2 cell[2];
    };
    Tmpl8::vec2 offset;
    Tmpl8::vec2 size;
    Tmpl8::vec2& operator [] (const int idx) { return cell[idx]; }
};

class BoxCollider :
    public Component
{
public:
    BoxCollider(Bounds bounds, CollisionType type) : 
        type(type),
        bounds(bounds)
    {}

    /// <summary>
    /// updates the position of the collider.
    /// </summary>
    /// <param name="entity"></param>
    virtual void Update(Entity& entity) override;
    
    /// <summary>
    /// gets the min and max pos of the collider
    /// </summary>
    /// <returns></returns>
    Bounds At() { return bounds; }

    /// <summary>
    /// gets the size of the collider
    /// </summary>
    /// <returns></returns>
    Tmpl8::vec2 GetSize() { return bounds.max - bounds.min; }

    /// <summary>
    /// checks if component collides at position
    /// </summary>
    /// <param name="pos"></param>
    /// <param name="b"></param>
    /// <returns></returns>
    bool CollidesAt(Tmpl8::vec2 pos, BoxCollider& b);


    /// <summary>
    /// checks if current component is colliding
    /// </summary>
    /// <param name="b"></param>
    /// <returns></returns>
    bool Collides(BoxCollider& b);

    /// <summary>
    /// checks if 2 boxcolliders collide
    /// </summary>
    /// <param name="a"></param>
    /// <param name="b"></param>
    /// <returns></returns>
    static bool Collides(BoxCollider& a, BoxCollider& b);
    static bool Collides(Entity& entity, Tmpl8::vec2 pos);

    CollisionType GetType() { return type; }
protected:
private:
    CollisionType type = CollisionType::none;
    Bounds bounds;
};
