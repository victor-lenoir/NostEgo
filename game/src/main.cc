#include "game/game.hh"
#define BUFFTIME 30

int g_w;
int g_h;

Game* g;

int main ()
{
  TTF_Init ();

  if (SDL_Init (SDL_INIT_VIDEO) < 0)
    return 42;

  g_w = SDL_GetVideoInfo()->current_w;
  g_h = SDL_GetVideoInfo()->current_h;

  g = new Game;
  Uint32 last = 0;
  Uint32 curr = 0;

  while (!g->done)
    {
      curr = SDL_GetTicks ();
      if (curr - last > BUFFTIME)
      {
	 g->process ();
	 g->display ();
	 last = curr;
      }
      else
	 SDL_Delay (BUFFTIME - (curr - last));
    }
  delete g;
  TTF_Quit ();

  return 0;
}
