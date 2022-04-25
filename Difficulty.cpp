#include "Difficulty.h"

#include "Exit.h"
#include "game.h"
#include "Menu.h"
#include "Reset.h"

void Difficulty::OnClick(Menu* menu)
{
  SetActive(false);

  for (const auto button : buttons)
  {
    button->SetActive(false);
  }

  reset->SetActive(true);

  menu->SetState(2);
  tmpl8::Game::Get().StartGame(difficulty);
}

void Difficulty::Left()
{
  if (IsActive() && difficulty != 1)
  {
    if (difficulty == 2)
    {
      buttons[0]->SetFucus(true);
    }
    else
    {
      buttons[1]->SetFucus(true);
    }
    SetFucus(false);
  }
}

void Difficulty::Right()
{
  if (IsActive() && difficulty != 3)
  {
    if (difficulty == 1)
    {
      buttons[0]->SetFucus(true);
    }
    else
    {
      buttons[1]->SetFucus(true);
    }
    SetFucus(false);
  }
}

void Difficulty::ButtonDown(Menu* menu)
{
  OnClick(menu);
  SetFucus(false);
}
