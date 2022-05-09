#pragma once
#include "Button.h"

#include "surface.h"
class Reset :
  public Button
{
public:
  Reset() :
    Button(new tmpl8::Sprite(new tmpl8::Surface("assets/UI/reset.png"), 2), 0.0f, true)
  {}

  /**
   * \brief Reset the game with the current difficulty
   * \param menu the menu the button is stored in
   */
  void OnClick(Menu* menu) override;
};

