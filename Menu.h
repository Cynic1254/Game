#pragma once

class Exit;
class Difficulty;
class Reset;
class Start;
class Button;

namespace tmpl8
{
  class Surface;
  class Sprite;
}

class Menu
{
public:
  Menu();

  ~Menu();

  void Render(tmpl8::Surface& dst) const;
  void MouseDown(int button);

  void MouseMove(int x, int y) const;

  int GetState() const { return state; }
  void SetState(int state) { this->state = state; }

  Exit* GetExitButton() const { return buttons.exit; }
private:
  tmpl8::Surface* menu;

  int state = 0;

  union
  {
    struct
    {
      Difficulty* easy;
      Difficulty* normal;
      Difficulty* hard;

      Start* start;
      Reset* reset;
      Exit* exit;
    };

    Button* array[6];
  } buttons;
};
