#pragma once
#include "Button.h"
#include "game.h"
#include "surface.h"

class Difficulty;

class Start :
  public Button
{
public:
  Start() :
    Button(new tmpl8::Sprite(new tmpl8::Surface("assets/UI/start.png"), 2), { ScreenWidth / 2.0f - 32, ScreenHeight / 2.0f - 16 }, true)
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
  void SetButtons(Difficulty& easy, Difficulty& normal, Difficulty& hard)
  {
    this->easy = &easy;
    this->normal = &normal;
    this->hard = &hard;
  }

  /**
   * \brief for game controllers, method get called on d-pad press
   */
  void Up() override;
  /**
   * \brief for game controllers, method get called on d-pad press
   */
  void Down() override;
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
  Difficulty* easy = nullptr;
  Difficulty* normal = nullptr;
  Difficulty* hard = nullptr;
};

