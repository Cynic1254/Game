#include "Button.h"

#include "surface.h"

Button::~Button()
{
  delete sprite;
}

void Button::MouseMove(int x, int y)
{
  const tmpl8::vec2 min = pos;
  const tmpl8::vec2 max = min + tmpl8::vec2{ static_cast<float>(sprite->GetWidth()), static_cast<float>(sprite->GetHeight()) };

  if (min.x < static_cast<float>(x) && max.x > static_cast<float>(x) && min.y < static_cast<float>(y) && max.y > static_cast<float>(y))
  {
    onButton = true;
  }
  else
  {
    onButton = false;
  }
}

void Button::Render(tmpl8::Surface* dst) const
{
  if(onButton)
  {
    sprite->SetFrame(1);
  } else
  {
    sprite->SetFrame(0);
  }
  if (active)
  {
    sprite->Draw(dst, static_cast<int>(pos.x), static_cast<int>(pos.y));
  }
}

void Button::Up()
{
}

void Button::Down()
{
}

void Button::Left()
{
}

void Button::Right()
{
}
