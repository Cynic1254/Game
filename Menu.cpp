#include "Menu.h"

#include "Difficulty.h"
#include "Exit.h"
#include "Reset.h"
#include "Start.h"
#include "surface.h"

Menu::Menu() : menu(new tmpl8::Surface(ScreenWidth, ScreenHeight)) // NOLINT(cppcoreguidelines-pro-type-member-init)
{
  buttons.start = new Start();
  buttons.reset = new Reset();
  buttons.exit = new Exit();

  buttons.easy = new Difficulty(new tmpl8::Sprite(new tmpl8::Surface("assets/UI/easy.png"), 1), {ScreenWidth / 2 - 64 - 128 - 10, ScreenHeight / 2 - 64}, 1);
  buttons.normal = new Difficulty(new tmpl8::Sprite(new tmpl8::Surface("assets/UI/normal.png"), 1), {ScreenWidth / 2 - 64, ScreenHeight / 2 - 64}, 2);
  buttons.hard = new Difficulty(new tmpl8::Sprite(new tmpl8::Surface("assets/UI/easy.png"), 1), {ScreenWidth / 2 - 64 + 128 + 10, ScreenHeight / 2 - 64}, 3);

  buttons.start->SetButtons(*buttons.easy, *buttons.normal, *buttons.hard);
  buttons.easy->SetButtons(*buttons.normal, *buttons.hard, *buttons.reset);
  buttons.normal->SetButtons(*buttons.easy, *buttons.hard, *buttons.reset);
  buttons.hard->SetButtons(*buttons.easy, *buttons.normal, *buttons.reset);
  buttons.exit->SetButtons(*buttons.easy, *buttons.normal, *buttons.hard);
}

Menu::~Menu()
{
  delete menu;
  for (const auto button : buttons.array)
  {
    delete button;
  }
}

void Menu::Render(tmpl8::Surface& dst) const
{
  menu->Clear(0x00);
  for (const auto & button : buttons.array)
  {
    button->Render(menu);
  }

  menu->Draw(&dst, 0,0);
}

void Menu::MouseMove(int x, int y) const
{
  for (const auto button : buttons.array)
  {
    button->MouseMove(x, y);
  }
}


void Menu::MouseDown(int button)
{
  switch (button)
  {
  case 1:
  case 2:
    for (auto button : buttons.array)
    {
      if(button->IsActive() && button->MouseOnButton())
        button->OnClick(this);
    }
    break;

  default:
    break;
  }
}
