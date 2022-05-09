#pragma once
#include "Button.h"
#include "game.h"
#include "surface.h"

class Exit;
class Difficulty;

class Start :
  public Button
{
public:
  Start() :
    Button(new tmpl8::Sprite(new tmpl8::Surface("assets/UI/start.png"), 2), { ScreenWidth / 2.0f - 32, ScreenHeight / 2.0f - 16 }, true, true)
  {}

  /**
   * \brief Go to difficulty select
   * \param menu the menu the button is stored in
   */
  void OnClick(Menu* menu) override;

  /**
   * \brief cache the buttons for later use
   * \param easy easy button
   * \param normal normal button
   * \param hard hard button
   */
  void SetButtons(Difficulty& easy, Difficulty& normal, Difficulty& hard, Exit& exit)
  {
    this->easy = &easy;
    this->normal = &normal;
    this->hard = &hard;
    this->exit = &exit;
  }

private:
  Difficulty* easy = nullptr;
  Difficulty* normal = nullptr;
  Difficulty* hard = nullptr;

  Exit* exit = nullptr;
};

