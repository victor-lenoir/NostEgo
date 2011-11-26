#include "game.hh"

#define VIDEO_FLAGS SDL_FULLSCREEN | SDL_HWSURFACE | SDL_DOUBLEBUF

Game::Game ()
{
   state = START;
   done = true;

   if (SDL_Init (SDL_INIT_VIDEO) < 0)
      return;

   w = g_w;
   h = g_h;

   if (!(screen = SDL_SetVideoMode (w, h, 32, VIDEO_FLAGS)))
      return;

  SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL);

  player.load ("healer.png", 8);
  done = false;
}

Game::~Game ()
{
  SDL_Quit ();
}

int Game::get_state ()
{
   return state;
}

void Game::set_state (int state_p)
{
   state = state_p;
   interface.clean ();
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
	case SDL_MOUSEBUTTONDOWN:
	   interface.process_mouse_click (event.motion.x, event.motion.y);
	   break;
	case SDL_KEYDOWN:
	   interface.process_keyboard (event.key.keysym.sym);
	   player.process_keyboard (event.key.keysym.sym);
	   if(event.key.keysym.sym == SDLK_ESCAPE)
	      done = true;
	   break;
     }
  }
}

void Game::display ()
{
  SDL_FillRect (screen,NULL, 0x000000);
  map.display (screen);
  interface.display (screen);
  SDL_Flip(screen);
}
