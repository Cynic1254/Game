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
  menu->GetExitButton()->SetDirections(nullptr, nullptr, reset, nullptr);
  tmpl8::Game::Get().StartGame(difficulty);
}
