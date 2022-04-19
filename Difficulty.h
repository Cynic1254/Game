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

  virtual void OnClick(Menu* menu) override;
protected:
private:
  int difficulty;
};

