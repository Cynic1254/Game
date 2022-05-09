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
  Button(tmpl8::Sprite* sprite, const tmpl8::vec2 pos = 0.0f, bool startOnButton = false, bool active = false) :
    pos(pos),
    sprite(sprite),
    active(active),
    startOnButton(startOnButton)
  {}

  virtual ~Button();

  /**
   * \brief The method that should run when the button gets clicked
   * \param menu the menu the button is stored in
   */
  virtual void OnClick(Menu* menu) {}

  /**
   * \brief mouse moved
   * \param x the x axis
   * \param y the y axis
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

  /**
   * \brief Determines if the button will render
   * \param state is the button active
   */
  void SetActive(bool state);

  /**
   * \brief will change the button frame to look "pressed"
   * \param state is the button "pressed"
   */
  void SetState(bool state) { onButton = state; }

  /**
   * \brief for game controllers, method get called on d-pad press
   */
  void Up();
  /**
   * \brief for game controllers, method get called on d-pad press
   */
  void Down();
  /**
   * \brief for game controllers, method get called on d-pad press
   */
  void Left();
  /**
   * \brief for game controllers, method get called on d-pad press
   */
  void Right();
  /**
   * \brief for game controllers, method gets called on button press
   * \param menu the menu the button is stored in
   */
  void ButtonDown(Menu* menu);

  void SetDirections(Button* up, Button* down, Button* left, Button* right) { this->up = up; this->down = down; this->left = left; this->right = right; }

private:
  Button* up = nullptr;
  Button* down = nullptr;
  Button* left = nullptr;
  Button* right = nullptr;
  const tmpl8::vec2 pos;
  tmpl8::Sprite* sprite;

  /**
   * \brief if the button needs to be rendered
   */
  bool active;

  /**
   * \brief if the button needs to show in a "pressed" state
   */
  bool onButton = false;

  const bool startOnButton = false;
  static Button* currentFocus;
};

