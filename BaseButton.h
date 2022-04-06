#pragma once

#include "template.h"

namespace tmpl8
{
  class Sprite;
}

class Button
{
public:
  Button(tmpl8::Sprite* sprite, tmpl8::vec2 pos = 0.0f, bool active = false) :
    pos(pos),
    sprite(sprite),
    active(active)
  {}

  virtual ~Button();

  virtual void OnClick() {}

	void MouseMove(int x, int y);

  bool IsActive() const { return active; }
  bool MouseOnButton() const {return onButton;}
  tmpl8::vec2 GetPos() const {return pos;}
  const tmpl8::Sprite* GetSprite() const {return sprite;}

protected:
private:
  tmpl8::vec2 pos;
  tmpl8::Sprite* sprite;
  bool active;
  bool onButton = false;
};

