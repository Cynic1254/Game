#include "Menu.h"

#include "BaseButton.h"
#include "game.h"
#include "surface.h"

void Menu::Render(tmpl8::Surface& dst) const
{
  menu->Clear(0x00);
  for (const auto & button : buttons)
  {
    if(button->IsActive())
    {
      button->GetSprite()->Draw(menu, static_cast<int>(button->GetPos().x), static_cast<int>(button->GetPos().y));
    }
  }

  menu->Draw(&dst, 0,0);
}

void Menu::MouseDown(int button)
{
  switch (button)
  {
  case 1:
  case 2:
    for (auto button : buttons)
    {
      if(button->IsActive() && button->MouseOnButton())
        button->OnClick();
    }
    break;

  default:
    break;
  }
}
