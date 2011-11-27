#include "game.hh"
#include <iostream>
#include <sstream>

#define VIDEO_FLAGS SDL_FULLSCREEN | SDL_HWSURFACE | SDL_DOUBLEBUF
//#define VIDEO_FLAGS SDL_HWSURFACE | SDL_DOUBLEBUF
std::string int_to_string (int n)
{
  std::ostringstream oss;
  oss << n;
  return oss.str();
}

Game::Game ()
{
  xoff = 0;
  yoff = 0;
  world_map = "test";
  xmap = 0;
  ymap = 0;
  state = START;
  done = true;

  if (!(screen = SDL_SetVideoMode (g_w, g_h, 32, VIDEO_FLAGS)))
    return;

  SDL_EnableKeyRepeat(100, SDL_DEFAULT_REPEAT_INTERVAL);

  player.load ("healer.png", 8);
  done = false;

  load_maps ();
}

Game::~Game ()
{
  SDL_Quit ();
}

void Game::load_maps ()
{
  std::string tmp = "media/maps/" + world_map;

  for (size_t y = 0; y < 3; ++y)
    for (size_t x = 0; x < 3; ++x)
      maps[x][y].load_map ((tmp + int_to_string (xmap + (x - 1)) + "-" +
			    int_to_string (ymap + (y - 1))).c_str ());
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
  Uint8 *keystate;

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
	case SDL_KEYUP:
	  keystate = SDL_GetKeyState(NULL);
	  player.process_keyboard (keystate);
	  break;
	case SDL_KEYDOWN:
	  keystate = SDL_GetKeyState(NULL);
	  player.process_keyboard (keystate);
	  interface.process_keyboard (event.key.keysym.sym);
	  if(event.key.keysym.sym == SDLK_ESCAPE)
	    done = true;
	  break;
	}
    }
}

void Game::display ()
{
  SDL_Rect tmp_rect;

  SDL_FillRect (screen,NULL, 0x000000);

  tmp_rect.x = tmp_rect.y = 0;
  tmp_rect.w = WIDTH_MAP;
  tmp_rect.h = HEIGHT_MAP;

  for (size_t y = 0; y < 3; ++y)
    for (size_t x = 0; x < 3; ++x)
      maps[x][y].display (screen,
			  (x - 1) * WIDTH_MAP + xoff,
			  (y - 1) * HEIGHT_MAP + yoff);

  interface.display (screen);
  SDL_Flip(screen);
}
