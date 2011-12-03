#include "game.hh"
#include <iostream>
#include <sstream>

std::string int_to_string (int n)
{
  std::ostringstream oss;
  oss << n;
  return oss.str();
}

void Game::init_game ()
{
  if (!init)
    {
      player = new Character;
      interface = new Interface;
      for (size_t x = 0; x < MAP_BUFFER; ++x)
	for (size_t y = 0; y < MAP_BUFFER; ++y)
	  maps[x][y] = new Map;
      player->load ("healer.png", 8);
      load_maps ();
      init = true;
    }
}

Game::Game ()
{
  init = false;
  player = 0;
  interface = 0;
  for (size_t x = 0; x < MAP_BUFFER; ++x)
    for (size_t y = 0; y < MAP_BUFFER; ++y)
      maps[x][y] = 0;

  xoff = 0;
  yoff = 0;
  world_map = "test";
  xmap = 0;
  ymap = 0;
  state = START;
  done = true;

  if (!(screen = SDL_SetVideoMode (opt->screen_w, opt->screen_h,
				   32,
				   opt->video_flags)))
    return;

  SDL_EnableKeyRepeat(100, SDL_DEFAULT_REPEAT_INTERVAL);
  done = false;
}

Game::~Game ()
{
  std::map<std::string, Element*>::iterator it;

  if (player)
    delete player;
  if (interface)
    delete interface;
  for (size_t x = 0; x < MAP_BUFFER; ++x)
    for (size_t y = 0; y < MAP_BUFFER; ++y)
      if (maps[x][y])
	delete maps[x][y];

  for (it = global_elements.begin();
       it != global_elements.end();
       it++)
    delete it->second;
  SDL_Quit ();
}

void Game::load_maps ()
{
  std::string tmp = "media/maps/" + world_map;

  for (size_t y = 0; y < MAP_BUFFER; ++y)
    for (size_t x = 0; x < MAP_BUFFER; ++x)
      maps[x][y]->load_map ((tmp + int_to_string (xmap + (x - MAP_BUFFER / 2))
			     + "-" +
			    int_to_string (ymap + (y - MAP_BUFFER / 2))).c_str ());
}

int Game::get_state ()
{
   return state;
}

void Game::set_state (int state_p)
{
   state = state_p;
   interface->clean ();
}

void Game::process ()
{
  SDL_Event event;
  Uint8* keystate = SDL_GetKeyState(NULL);

  if (state == MAP)
  {
     player->process_keyboard (keystate);
     maps[MAP_BUFFER / 2][MAP_BUFFER / 2]->process_keyboard (keystate);
  }

  while (SDL_PollEvent(&event))
    {
      switch (event.type)
	{
	case SDL_MOUSEMOTION:
	  interface->process_mouse (event.motion.x, event.motion.y);
	  break;
	case SDL_MOUSEBUTTONDOWN:
	  interface->process_mouse_click (event.motion.x, event.motion.y);
	  break;
	case SDL_KEYDOWN:
	  interface->process_keyboard (event.key.keysym.sym);
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


  if (g->get_state() == MAP)
    {
      for (int y = MAP_BUFFER - 1; y >= 0; --y)
	for (size_t x = 0; x < MAP_BUFFER; ++x)
	  {
	    maps[x][y]->display_background (screen,
					    (x - MAP_BUFFER / 2) * WIDTH_MAP + xoff,
					    (y - MAP_BUFFER / 2) * HEIGHT_MAP + yoff);
	  }

    for (int y = MAP_BUFFER - 1; y >= 0; --y)
      for (size_t x = 0; x < MAP_BUFFER; ++x)
	{
	  maps[x][y]->display (screen,
			       (x - MAP_BUFFER / 2) * WIDTH_MAP + xoff,
			       (y - MAP_BUFFER / 2) * HEIGHT_MAP + yoff,
			       (x != MAP_BUFFER / 2) || (y != MAP_BUFFER / 2));
	}
    }

  interface->display (screen);
  SDL_Flip(screen);
}
