#include "game/game.hh"
#define BUFFTIME 30

int g_w = 1920;
int g_h = 1200;

int main ()
{
  Game g;
  Uint32 last = 0;
  Uint32 curr = 0;

  while (!g.done)
    {
      curr = SDL_GetTicks ();
      if (curr - last > BUFFTIME)
      {
	 g.process ();
	 g.display ();
	 last = curr;
      }
      else
	 SDL_Delay (BUFFTIME - (curr - last));
    }

  return 0;
}
