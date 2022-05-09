#include "Exit.h"

#include "Difficulty.h"
#include "game.h"
#include "Menu.h"
#include "Reset.h"
#include "template.h"

void Exit::OnClick(Menu* menu)
{
  switch (menu->GetState())
  {
  case 0:
  case 1:
    ExitProgram();
    break;
  case 2:
  case 3:
    menu->SetState(1);

    easy->SetActive(true);
    normal->SetActive(true);
    hard->SetActive(true);

    reset->SetActive(false);

    SetDirections(nullptr, hard, nullptr, nullptr);

    tmpl8::Game::Get().EndGame();
    break;
  default:
    break;
  }
}
