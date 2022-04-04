#pragma once

#include "template.h"

#include <vector>

namespace tmpl8
{
  class Surface;
  class Sprite;
}

class Menu
{
public:
  Menu(tmpl8::Surface* menu) :
    menu(menu)
  {}

  void Render(tmpl8::Surface& dst) const;
  void MouseDown(int button);
protected:
private:
  struct Button
  {
    Button(const char* id, tmpl8::Sprite* sprite, tmpl8::vec2 pos = 0.0f, bool active = false) :
      pos(pos),
      sprite(sprite),
      active(active),
      id(id)
    {}

    bool Clicked(tmpl8::vec2 clickPos) const;

    tmpl8::vec2 pos;
    tmpl8::Sprite* sprite;
    bool active;

    const char* id;
  };

  tmpl8::Surface* menu;

  std::vector<Button> buttons;
};
