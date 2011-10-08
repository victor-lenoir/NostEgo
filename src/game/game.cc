#include "game.hh"

Game::Game ()
{
  if (SDL_Init (SDL_INIT_VIDEO) < 0 )
    done = true;
  else if (!(screen = SDL_SetVideoMode (WIDTH, HEIGHT, 32, SDL_FULLSCREEN
					| SDL_HWSURFACE | SDL_DOUBLEBUF)))
    done = true;
  else
    done = false;

  SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
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
