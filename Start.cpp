#include "Start.h"

#include "Menu.h"

void Start::OnClick(Menu* menu)
{
  SetActive(false);

  easy->SetActive(true);
  normal->SetActive(true);
  hard->SetActive(true);

  menu->SetState(1);
}
