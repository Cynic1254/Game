#include "Difficulty.h"

#include "game.h"
#include "Menu.h"

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
