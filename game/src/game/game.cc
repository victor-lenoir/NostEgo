#include "game.hh"
#include <iostream>
#include <sstream>

std::string int_to_string (int n)
{
  std::ostringstream oss;
  oss << n;
  return oss.str();
}

Game::Game ()
{
  //xoff = -(MAP_BUFFER / 2 - 1) * WIDTH_MAP;
  //yoff = -(MAP_BUFFER / 2 - 1) * HEIGHT_MAP;
  world_map = "test";
  xmap = 1;
  ymap = 1;
  state = START;
  done = true;

  if (!(screen = SDL_SetVideoMode (opt->screen_w, opt->screen_h,
				   32,
				   opt->video_flags)))
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

  for (size_t y = 0; y < MAP_BUFFER; ++y)
    for (size_t x = 0; x < MAP_BUFFER; ++x)
      maps[x][y].load_map ((tmp + int_to_string (xmap + (x - MAP_BUFFER / 2)) + "-" +
			    int_to_string (ymap + (y - MAP_BUFFER / 2))).c_str ());
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
  Uint8* keystate = SDL_GetKeyState(NULL);

  player.process_keyboard (keystate);
  maps[1][1].process_keyboard (keystate);

  while (SDL_PollEvent(&event))
    {
      player.process_keyboard (keystate);
      maps[1][1].process_keyboard (keystate);
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

  for (size_t y = 0; y < MAP_BUFFER; ++y)
    for (size_t x = 0; x < MAP_BUFFER; ++x)
      maps[x][y].display (screen,
			  (x - 1) * WIDTH_MAP + xoff,
			  (y - 1) * HEIGHT_MAP + yoff);

  interface.display (screen);
  SDL_Flip(screen);
}
