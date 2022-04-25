#pragma once
#include "Button.h"

namespace tmpl8
{
  class Sprite;
}

class Reset;

class Difficulty :
  public Button
{
public:
  Difficulty(tmpl8::Sprite* sprite, tmpl8::vec2 pos, int difficulty) :
    Button(sprite, pos),
    difficulty(difficulty)
  {}

  /**
   * \brief cache the buttons for use
   * \param button1 lowest difficulty button
   * \param button2 highest difficulty button
   * \param reset reset button
   */
  void SetButtons(Difficulty& button1, Difficulty& button2, Reset& reset) { buttons[0] = &button1; buttons[1] = &button2; this->reset = &reset; }

  /**
   * \brief Start the game with the given difficulty
   * \param menu the menu the button is stored in
   */
  void OnClick(Menu* menu) override;

  /**
   * \brief for game controllers, method get called on d-pad press
   */
  void Left() override;
  /**
   * \brief for game controllers, method get called on d-pad press
   */
  void Right() override;

  /**
   * \brief for game controllers, method gets called on button press
   * \param menu the mnu the button is stored in
   */
  void ButtonDown(Menu* menu) override;
private:
  Difficulty* buttons[2] = { nullptr, nullptr };

  Reset* reset = nullptr;

  int difficulty;
};

