#include "game/game.hh"

int g_w = 1920;
int g_h = 1200;

int main ()
{
  Game g;

  while (!g.done)
    {
      g.process ();
      g.display ();
    }

  return 0;
}
