#include "Start.h"

#include "Difficulty.h"
#include "Exit.h"
#include "Menu.h"

void Start::OnClick(Menu* menu)
{
  SetActive(false);

  easy->SetActive(true);
  normal->SetActive(true);
  hard->SetActive(true);
  exit->SetActive(true);

  menu->SetState(1);
}
