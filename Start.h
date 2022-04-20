#pragma once
#include "Button.h"

#include "surface.h"
class Start :
  public Button
{
public:
  Start() :
    Button(new tmpl8::Sprite(new tmpl8::Surface("assets/UI/start.png"), 2), { ScreenWidth / 2.0f - 32, ScreenHeight / 2.0f - 16 }, true)
  {}

  void OnClick(Menu* menu) override;

  void SetButtons(Button& easy, Button& normal, Button& hard)
  {
    this->easy = &easy;
    this->normal = &normal;
    this->hard = &hard;
  }

private:
  Button* easy = nullptr;
  Button* normal = nullptr;
  Button* hard = nullptr;
};

