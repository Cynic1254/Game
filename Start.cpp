#include "Start.h"

#include "Difficulty.h"
#include "Menu.h"

void Start::OnClick(Menu* menu)
{
  SetActive(false);

  easy->SetActive(true);
  normal->SetActive(true);
  hard->SetActive(true);

  menu->SetState(1);
}

void Start::Up()
{
  SetFucus(true);
}

void Start::Down()
{
  SetFucus(true);
}

void Start::Left()
{
  SetFucus(true);
}

void Start::Right()
{
  SetFucus(true);
}

void Start::ButtonDown(Menu* menu)
{
  OnClick(menu);
  normal->SetFucus(true);
}
