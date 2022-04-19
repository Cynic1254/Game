#include "Exit.h"

#include "game.h"
#include "Menu.h"
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
    menu->SetState(1);

    easy->SetActive(true);
    normal->SetActive(true);
    hard->SetActive(true);

    tmpl8::Game::Get().EndGame();
    break;
  default:
    return;
  }
}
