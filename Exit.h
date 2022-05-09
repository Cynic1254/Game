#pragma once
#include "Button.h"
#include "surface.h"
#include "game.h"

class Difficulty;
class Reset;

class Exit :
  public Button
{
public:
  Exit() :
    Button(new tmpl8::Sprite(new tmpl8::Surface("assets/UI/exit.png"), 2), { ScreenWidth - 64, 0 }, true)
  {}

  /**
   * \brief return to the menu if game is running and close program if on menu
   * \param menu the menu the button is stored in
   */
  void OnClick(Menu* menu) override;

  /**
   * \brief cache the buttons for use
   * \param easy easy button
   * \param normal normal button
   * \param hard hard button
   * \param reset reset button
   */
  void SetButtons(Difficulty& easy, Difficulty& normal, Difficulty& hard, Reset& reset)
  {
    this->easy = &easy;
    this->normal = &normal;
    this->hard = &hard;
    this->reset = &reset;
  }

private:
  Difficulty* easy = nullptr;
  Difficulty* normal = nullptr;
  Difficulty* hard = nullptr;

  Reset* reset = nullptr;
};

