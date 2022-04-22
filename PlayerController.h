#pragma once
#include <SDL_scancode.h>

#include "Component.h"
#include "Timer.h"

class AudioPlayer;
class Entity;

class PlayerController :
  public Component
{
public:
  PlayerController();

  void Update(Entity& entity) override;

  void KeyDown(Entity& entity, SDL_Scancode key) override;
  void KeyUp(Entity& entity, SDL_Scancode key) override;

  /// <summary>
  /// player got hurt
  /// </summary>
  /// <param name="entity"></param>
  void Hurt(Entity& entity) override;

  static float GetYMovement();
  static int GetLives() { return lives; }
  static int GetScore() { return static_cast<int>(score); }

  void SetActive(Entity& entity, bool state) override;

  void JoystickMove(Uint8 axis, Sint16 value) override;
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

  static double score;

  double controllerAxis = 0.0;

  AudioPlayer* hurt{};
  AudioPlayer* death{};
};
