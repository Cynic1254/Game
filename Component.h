#pragma once

//component structure copied from jeremiah

#include <SDL_scancode.h>
#include <utility>

namespace tmpl8 {
    class Surface;
}

class Entity;
class BoxCollider;

class Component
{
public:

    virtual ~Component() = default;

    /// <summary>
    /// update the Component
    /// </summary>
    virtual void Update(Entity& entity);

    /// <summary>
    /// Render the Component
    /// </summary>
    virtual void Render(Entity& entity, tmpl8::Surface& screen);

    /// <summary>
    /// A key was Released
    /// </summary>
    /// <param name="entity"></param>
    /// <param name="key"></param>
    virtual void KeyUp(Entity& entity, SDL_Scancode key);

    /// <summary>
    /// A key was Pressed
    /// </summary>
    /// <param name="entity"></param>
    /// <param name="key"></param>
    virtual void KeyDown(Entity& entity, SDL_Scancode key);

    /// <summary>
    /// The mouse was moved
    /// </summary>
    /// <param name="entity"></param>
    /// <param name="x"></param>
    /// <param name="y"></param>
    virtual void MouseMove(Entity& entity, int x, int y);

    /// <summary>
    /// A mouse button was released
    /// </summary>
    /// <param name="entity"></param>
    /// <param name="key"></param>
    virtual void MouseUp(Entity& entity, int key);


    /// <summary>
    /// A mouse button was pressed
    /// </summary>
    /// <param name="entity"></param>
    /// <param name="key"></param>
    virtual void MouseDown(Entity& entity, int key);

    /// <summary>
    /// entity collides with blocking entity
    /// </summary>
    /// <param name="self"></param>
    /// <param name="other"></param>
    /// <param name="colliders"></param>
    virtual void CollidesWith(Entity& self, Entity& other, std::pair<BoxCollider*, BoxCollider*> colliders);

    /// <summary>
    /// entity collides with hurting entity
    /// </summary>
    /// <param name="self"></param>
    virtual void Hurt(Entity& self);

    /// <summary>
    /// activates / deactivates the component
    /// </summary>
    /// <param name="entity"></param>
    /// <param name="state"></param>
    virtual void SetActive(Entity& entity, bool state) { isActive = state; }
    bool GetState() const { return isActive; }
protected:
    /// <summary>
    /// Do not implement directly
    /// </summary>
    Component() = default;

    bool isActive = true;
private:
};