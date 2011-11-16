#include "game.hh"

#define VIDEO_FLAGS SDL_FULLSCREEN | SDL_HWSURFACE | SDL_DOUBLEBUF

Game::Game ()
{
   done = true;

   if (SDL_Init (SDL_INIT_VIDEO) < 0)
      return;

   w = g_w;
   h = g_h;

   if (!(screen = SDL_SetVideoMode (w, h, 32, VIDEO_FLAGS)))
      return;

  SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);

  done = false;
}

Game::~Game ()
{
  SDL_Quit ();
}

void Game::process ()
{
  process_exit ();
  interface.process ();
}

void Game::process_exit ()
{
  SDL_Event event;

  if (SDL_PollEvent(&event))
    {
      switch (event.type)
	{
	case SDL_KEYDOWN:
	  if(event.key.keysym.sym == SDLK_ESCAPE)
	    done = true;
	  break;
	}
    }
}

void Game::display ()
{
  interface.display (screen);
  SDL_Flip(screen);
}
