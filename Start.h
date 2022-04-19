#pragma once
#include "Button.h"

#include "surface.h"
class Start :
    public Button
{
public:
  Start() :
  Button(new tmpl8::Sprite(new tmpl8::Surface("assets/UI/start.png"), 2), {ScreenWidth / 2 - 32, ScreenHeight / 2 - 16}, true)
  {}

  virtual void OnClick(Menu* menu) override;

  void SetButtons(Button& easy, Button& normal, Button& hard)  // NOLINT(clang-diagnostic-shadow)
  {
    this->easy = &easy;
    this->normal = &normal;
    this->hard = &hard;
  }

protected:
private:
  Button* easy = nullptr;
  Button* normal = nullptr;
  Button* hard = nullptr;
};

