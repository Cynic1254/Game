#pragma once
#include <SDL_scancode.h>

#include "Component.h"
#include "Timer.h"

class Entity;

class PlayerController :
    public Component
{
public:
    PlayerController() :
        timer(Timer::Get())
    {}

    virtual void Update(Entity& entity) override;

    virtual void KeyDown(Entity& entity, SDL_Scancode key) override;
    virtual void KeyUp(Entity& entity, SDL_Scancode key) override;

    /// <summary>
    /// player got hurt
    /// </summary>
    /// <param name="entity"></param>
    virtual void Hurt(Entity& entity) override;

    static double GetYMovement() { return yMovement; }
protected:
private:
    Timer& timer;

    bool left = false;
    bool right = false;

    double invincibility = 1;
    int lives = 3;

    static double yMovement;
};
