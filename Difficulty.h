#pragma once
#include "Button.h"

namespace tmpl8
{
  class Sprite;
}

class Difficulty :
  public Button
{
public:
  Difficulty(tmpl8::Sprite* sprite, tmpl8::vec2 pos, int difficulty) :
    Button(sprite, pos),
    difficulty(difficulty)
  {}

  void SetButtons(Button& button1, Button& button2, Button& reset) { buttons[0] = &button1; buttons[1] = &button2; this->reset = &reset; }

  void OnClick(Menu* menu) override;
private:
  Button* buttons[2] = { nullptr, nullptr };

  Button* reset = nullptr;

  int difficulty;
};

