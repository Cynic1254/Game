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

  /**
   * \brief The method that should run when the button gets clicked
   * \param menu the menu the button is stored in
   */
  virtual void OnClick(Menu* menu) {}

  /**
   * \brief mouse moved
   * \param x 
   * \param y 
   */
  void MouseMove(int x, int y);

  /**
   * \brief render the button
   * \param dst destination surface
   */
  void Render(tmpl8::Surface* dst) const;

  bool IsActive() const { return active; }
  bool MouseOnButton() const { return onButton; }
  tmpl8::vec2 GetPos() const { return pos; }

  void SetActive(bool state) { active = state; }

  void SetFucus(bool state) { onButton = state; }

  /**
   * \brief for game controllers, method get called on d-pad press
   */
  virtual void Up();
  /**
   * \brief for game controllers, method get called on d-pad press
   */
  virtual void Down();
  /**
   * \brief for game controllers, method get called on d-pad press
   */
  virtual void Left();
  /**
   * \brief for game controllers, method get called on d-pad press
   */
  virtual void Right();
  /**
   * \brief for game controllers, method gets called on button press
   * \param menu the mnu the button is stored in
   */
  virtual void ButtonDown(Menu* menu) {}

private:
  const tmpl8::vec2 pos;
  tmpl8::Sprite* sprite;
  bool active;
  bool onButton = false;
};

