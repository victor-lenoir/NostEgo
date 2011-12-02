#include "game/game.hh"

Game* g;
Option* opt;

int main ()
{
  opt = new Option;
  g = new Game;
  g->init_game ();
  Uint32 last = 0;
  Uint32 curr = 0;

  while (!g->done)
    {
      curr = SDL_GetTicks ();
      if (curr - last > (1000 / opt->fps))
      {
	if (g->init)
	  {
	    opt->curr_fps = 1000 / (curr - last);
	    g->process ();
	    g->display ();
	  }
	 last = curr;
      }
      else
	SDL_Delay ((1000 / opt->fps) - (curr - last));
    }
  delete g;
  delete opt;
  TTF_Quit ();

  return 0;
}
