#include "Menu.h"

#include "Difficulty.h"
#include "Exit.h"
#include "PlayerController.h"
#include "Reset.h"
#include "Start.h"
#include "surface.h"

Menu::Menu() : menu(new tmpl8::Surface(ScreenWidth, ScreenHeight)) // NOLINT(cppcoreguidelines-pro-type-member-init)
{
  buttons.start = new Start();
  buttons.reset = new Reset();
  buttons.exit = new Exit();

  buttons.easy = new Difficulty(new tmpl8::Sprite(new tmpl8::Surface("assets/UI/easy.png"), 1), { ScreenWidth / 2.0f - 64 - 128 - 10, ScreenHeight / 2.0f - 64 }, 1);
  buttons.normal = new Difficulty(new tmpl8::Sprite(new tmpl8::Surface("assets/UI/normal.png"), 1), { ScreenWidth / 2.0f - 64, ScreenHeight / 2.0f - 64 }, 2);
  buttons.hard = new Difficulty(new tmpl8::Sprite(new tmpl8::Surface("assets/UI/hard.png"), 1), { ScreenWidth / 2.0f - 64 + 128 + 10, ScreenHeight / 2.0f - 64 }, 3);

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
  menu->Clear(0);
  for (const auto& button : buttons.array)
  {
    button->Render(menu);
  }

  if (state == 0)
  {
    menu->Print("Generic slalom game", 120, 150, 0x010101, 5);
  }

  if (state == 1)
  {
    menu->Print("Select Difficulty", 150, 150, 0x010101, 5);
  }

  if (state == 2)
  {
    char text[50];
    sprintf(text, "Score: %i", PlayerController::GetScore());

    menu->Print(text, 70, 5, 0x010101, 2);
  }

  if (state == 3)
  {
    char text[50];
    sprintf(text, "Score: %i", PlayerController::GetScore());

    menu->Print(text, 200, 200, 0x010101, 2);
  }

  menu->Draw(&dst, 0, 0);
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
    for (const auto button1 : buttons.array)
    {
      if (button1->IsActive() && button1->MouseOnButton())
        button1->OnClick(this);
    }
    break;

  default:
    break;
  }
}
