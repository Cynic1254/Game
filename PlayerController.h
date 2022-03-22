#pragma once
#include "Component.h"
#include "Timer.h"

#include <SDL_scancode.h>

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
