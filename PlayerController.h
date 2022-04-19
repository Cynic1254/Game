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
  {
  }

  void Update(Entity& entity) override;

  void KeyDown(Entity& entity, SDL_Scancode key) override;
  void KeyUp(Entity& entity, SDL_Scancode key) override;

  /// <summary>
  /// player got hurt
  /// </summary>
  /// <param name="entity"></param>
  void Hurt(Entity& entity) override;

  static float GetYMovement();
  static int GetLives() {return lives;}

  virtual void SetActive(Entity& entity, bool state) override;

protected:
private:
  Timer& timer;

  bool left = false;
  bool right = false;
  bool up = false;
  bool down = false;

  double invincibility = 1;
  static int lives;

  static float yMovement;
  static bool isActive;
};
