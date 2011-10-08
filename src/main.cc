#include "game/game.hh"

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
