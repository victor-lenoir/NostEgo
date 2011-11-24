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
  SDL_Event event;

  while (SDL_PollEvent(&event))
  {
     switch (event.type)
     {
	case SDL_MOUSEMOTION:
	   interface.process_mouse (event.motion.x, event.motion.y);
	   break;
	case SDL_KEYDOWN:
	   if(event.key.keysym.sym == SDLK_ESCAPE)
	      done = true;
	   break;
     }
  }
}

void Game::display ()
{
  SDL_FillRect (screen,NULL, 0x000000);
  interface.display (screen);
  SDL_Flip(screen);
}
