#pragma once

#include <vector>

class Button;

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

  void AddButton(Button* button) {buttons.push_back(button);}
protected:
private:

  tmpl8::Surface* menu;

  std::vector<Button*> buttons;
};
