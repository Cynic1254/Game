#include "BaseButton.h"

#include "surface.h"

Button::~Button()
{
  delete sprite;
}

void Button::MouseMove(int x, int y)
{
  const tmpl8::vec2 min = pos;
  const tmpl8::vec2 max = min + tmpl8::vec2{static_cast<float>(sprite->GetWidth()), static_cast<float>(sprite->GetHeight())};

  if (min.x < static_cast<float>(x) && max.x > static_cast<float>(x) && min.y < static_cast<float>(y) && max.y > static_cast<float>(y))
  {
    sprite->SetFrame(1);
    onButton = true;
  }
  else
  {
    sprite->SetFrame(0);
    onButton = false;
  }
}