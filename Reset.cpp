#include "Reset.h"

#include "game.h"

void Reset::OnClick(Menu* menu)
{
  tmpl8::Game::Get().StartGame(tmpl8::Game::Get().GetDifficulty());
}
