#include "Button.h"

#include "surface.h"

Button* Button::currentFocus = nullptr;

Button::~Button()
{
  delete sprite;
}

void Button::MouseMove(int x, int y)
{
  const tmpl8::vec2 min = pos;
  const tmpl8::vec2 max = min + tmpl8::vec2{ static_cast<float>(sprite->GetWidth()), static_cast<float>(sprite->GetHeight()) };

  //check if mouse is on button
  if (min.x < static_cast<float>(x) && max.x > static_cast<float>(x) && min.y < static_cast<float>(y) && max.y > static_cast<float>(y))
  {
    onButton = true;
    if (active)
    {
      currentFocus = this;
    }
  }
  else
  {
    onButton = false;
  }
}

void Button::Render(tmpl8::Surface* dst) const
{
  if (onButton)
  {
    sprite->SetFrame(1);
  }
  else
  {
    sprite->SetFrame(0);
  }
  if (active)
  {
    sprite->Draw(dst, static_cast<int>(pos.x), static_cast<int>(pos.y));
  }
}

void Button::SetActive(bool state)
{
  active = state;
  onButton = false;
}

void Button::Up()
{
  if (active && currentFocus == nullptr && startOnButton)
  {
    currentFocus = this;
    onButton = true;
    return;
  }

  if (currentFocus == this && !onButton)
  {
    onButton = true;
    return;
  }

  if (currentFocus != this || up == nullptr)
    return;

  currentFocus = up;
  onButton = false;
  currentFocus->SetState(true);
}

void Button::Down()
{
  if (active && currentFocus == nullptr && startOnButton)
  {
    currentFocus = this;
    onButton = true;
    return;
  }

  if (currentFocus == this && !onButton)
  {
    onButton = true;
    return;
  }

  if (currentFocus != this || down == nullptr)
    return;

  currentFocus = down;
  onButton = false;
  currentFocus->SetState(true);
}

void Button::Left()
{
  if (active && currentFocus == nullptr && startOnButton)
  {
    currentFocus = this;
    onButton = true;
    return;
  }

  if (currentFocus == this && !onButton)
  {
    onButton = true;
    return;
  }

  if (currentFocus != this || left == nullptr)
    return;

  currentFocus = left;
  onButton = false;
  currentFocus->SetState(true);
}

void Button::Right()
{
  if (active && currentFocus == nullptr && startOnButton)
  {
    currentFocus = this;
    onButton = true;
    return;
  }

  if (currentFocus == this && !onButton)
  {
    onButton = true;
    return;
  }

  if (currentFocus != this || right == nullptr)
    return;

  currentFocus = right;
  onButton = false;
  currentFocus->SetState(true);
}

void Button::ButtonDown(Menu* menu)
{
  if (currentFocus != this || !onButton)
    return;

  this->OnClick(menu);
  currentFocus = nullptr;
  SetState(false);
}
