#pragma once

//component structure copied from jeremiah

#include <SDL_scancode.h>
#include <string>

namespace Tmpl8 {
    class Surface;
}

class Entity;

class Component
{
public:

    /// <summary>
    /// update the Component
    /// </summary>
    virtual void Update(Entity& entity);

    /// <summary>
    /// Render the Component
    /// </summary>
    virtual void Render(Entity& entity, Tmpl8::Surface& screen);

    /// <summary>
    /// A key was Released
    /// </summary>
    /// <param name="key"></param>
    virtual void KeyUp(Entity& entity, SDL_Scancode key);

    /// <summary>
    /// A key was Pressed
    /// </summary>
    /// <param name="key"></param>
    virtual void KeyDown(Entity& entity, SDL_Scancode key);

    /// <summary>
    /// The mouse was moved
    /// </summary>
    /// <param name="x"></param>
    /// <param name="y"></param>
    virtual void MouseMove(Entity& entity, int x, int y);

    /// <summary>
    /// A mouse button was released
    /// </summary>
    /// <param name="key"></param>
    virtual void MouseUp(Entity& entity, int key);


    /// <summary>
    /// A mouse button was pressed
    /// </summary>
    /// <param name="key"></param>
    virtual void MouseDown(Entity& entity, int key);

    virtual ~Component() = default;
protected:
    /// <summary>
    /// Do not implement directly
    /// </summary>
    Component() = default;
private:
};