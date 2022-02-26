#pragma once
#include "Component.h"
#include "template.h"

class Transform :
    public Component
{
public:
    Transform() : position(0.0f) {};
    Transform(Tmpl8::vec2 position) : 
        position(position)
    {};

    /// <summary>
    /// set the position
    /// </summary>
    /// <param name="position"></param>
    void SetPosition(Tmpl8::vec2 position);

    /// <summary>
    /// adds the position to the current position
    /// </summary>
    /// <param name="position"></param>
    void AddPosition(Tmpl8::vec2 position);

    /// <summary>
    /// adds the position to the current position with collision
    /// </summary>
    /// <param name="entity"></param>
    /// <param name="position"></param>
    /// <returns></returns>
    bool CollisionAdd(Entity& entity, Tmpl8::vec2 position);

    /// <summary>
    /// returns the position
    /// </summary>
    /// <returns></returns>
    Tmpl8::vec2 GetPosition();

    /// <summary>
    /// returns the screen position
    /// </summary>
    /// <returns></returns>
    static Tmpl8::vec2 GetScreenPosition();

    /// <summary>
    /// sets the screenposition
    /// </summary>
    /// <param name="screenPosition"></param>
    static void SetScreenPosition(Tmpl8::vec2 screenPosition);

    static void AddScreenPosition(Tmpl8::vec2 screenPosition);
protected:
private:
    Tmpl8::vec2 position;
    static Tmpl8::vec2 screenPosition;
};
