#pragma once

#include "template.h"

class Menu;

namespace tmpl8
{
  class Surface;
  class Sprite;
}

enum class GameStates
{
  always,
  mainMenu,
  settings,
  game,
  difficultySellect
};

class Button
{
public:
  Button(tmpl8::Sprite* sprite, const tmpl8::vec2 pos = 0.0f, bool active = false) :
    pos(pos),
    sprite(sprite),
    active(active)
  {}

  virtual ~Button();

  virtual void OnClick(Menu* menu) {}

  void MouseMove(int x, int y);

  void Render(tmpl8::Surface* dst) const;

  bool IsActive() const { return active; }
  bool MouseOnButton() const { return onButton; }
  tmpl8::vec2 GetPos() const { return pos; }

  void SetActive(bool state) { active = state; }

  void SetFucus(bool state) { onButton = state; }

  virtual void Up();
  virtual void Down();
  virtual void Left();
  virtual void Right();

  virtual void ButtonDown(Menu* menu) {}

private:
  const tmpl8::vec2 pos;
  tmpl8::Sprite* sprite;
  bool active;
  bool onButton = false;
};

