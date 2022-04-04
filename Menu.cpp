#include "Menu.h"

#include "game.h"
#include "surface.h"

void Menu::Render(tmpl8::Surface& dst) const
{
  menu->Clear(0x00);
  for (const auto & button : buttons)
  {
    if(button.active)
    {
      button.sprite->Draw(menu, static_cast<int>(button.pos.x), static_cast<int>(button.pos.y));
    }
  }

  menu->CopyTo(&dst, 0,0);
}

void Menu::MouseDown(int button)
{
}

bool Menu::Button::Clicked(const tmpl8::vec2 clickPos) const
{
  if(!active)
    return false;

  const tmpl8::vec2 min = pos;
  const tmpl8::vec2 max = pos + tmpl8::vec2{static_cast<float>(sprite->GetWidth()), static_cast<float>(sprite->GetHeight())};

  return (clickPos.x > min.x && clickPos.x < max.x && clickPos.y > min.y && clickPos.y < max.y);
}
