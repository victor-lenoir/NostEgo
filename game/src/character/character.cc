#include "character.hh"
#include "../game/game.hh"
#include <iostream>
#include "../map/map.hh"

#define SQRT2 sqrt(2) / 2.0

enum
  {
    DOWN,
    LEFT,
    RIGHT,
    UP,
    DOWN_LEFT,
    DOWN_RIGHT,
    UP_LEFT,
    UP_RIGHT
  };

extern Game* g;
void Character::display (SDL_Surface* screen)
{
  animation.display (screen);
}

void Character::move (float x,
		      float y,
		      int dir_p)
{
  float deltax = 4.0;
  float deltay = 4.0;
  curr = SDL_GetTicks ();

  if (last > 0)
    {
      deltax = (curr - last) / 5.0;
      deltay = (curr - last) / 5.0;
      if (deltax > 4.0)
	deltax = 4.0;
      if (deltay > 4.0)
	deltay = 4.0;
    }

  deltax *= x;
  deltay *= y;

  deltax *= 4;
  deltay *= 4;
  dir = dir_p;

  if ((int)deltax > 0)
    {
      if ((int)animation.rect.x > 3 * g_w / 4)
	g->xoff -= (int)deltax;
      else
	animation.rect.x += (int)deltax;
    }
  else
    {
      if ((int)animation.rect.x < g_w / 4)
	g->xoff -= (int)deltax;
      else
	animation.rect.x += (int)deltax;
    }

  if ((int)deltay > 0)
    {
      if ((int)animation.rect.y > 3 * g_h / 4)
        g->yoff -= (int)deltay;
      else
        animation.rect.y += (int)deltay;
    }
  else
    {
      if ((int)animation.rect.y < g_h / 4)
        g->yoff -= (int)deltay;
      else
        animation.rect.y += (int)deltay;
    }

  if (g->xoff < -(WIDTH_MAP / 2))
    {
      g->xoff += WIDTH_MAP;
      ++g->xmap;
      g->load_maps ();
    }
  if (g->xoff > WIDTH_MAP / 2)
    {
      g->xoff -= WIDTH_MAP;
      --g->xmap;
      g->load_maps ();
    }

  if (g->yoff < -(HEIGHT_MAP / 2))
    {
      g->yoff += HEIGHT_MAP;
      ++g->ymap;
      g->load_maps ();
    }
  if (g->yoff > (HEIGHT_MAP / 2))
    {
      g->yoff -= HEIGHT_MAP;
      --g->ymap;
      g->load_maps ();
    }

  animation.stepping = true;
  animation.mask.y = dir * (animation.img->h / 8);
  last = curr;
}

void Character::stand ()
{
  animation.step = 0;
  animation.stepping = false;
  animation.playing = false;
}

void Character::process_keyboard (Uint8 *keystate)
{
  if (g->get_state() != MAP)
    return;

  if (keystate[SDLK_UP] && keystate[SDLK_RIGHT])
    move (SQRT2, -SQRT2, UP_RIGHT);
  else if (keystate[SDLK_DOWN] && keystate[SDLK_RIGHT])
    move (SQRT2, SQRT2, DOWN_RIGHT);
  else if (keystate[SDLK_UP] && keystate[SDLK_LEFT])
    move (-SQRT2, -SQRT2, UP_LEFT);
  else if (keystate[SDLK_DOWN] && keystate[SDLK_LEFT])
    move (-SQRT2, SQRT2, DOWN_LEFT);
  else if (keystate[SDLK_UP])
    move (0, -1, UP);
  else if (keystate[SDLK_DOWN])
    move (0, 1, DOWN);
  else if (keystate[SDLK_RIGHT])
    move (1, 0, RIGHT);
  else if (keystate[SDLK_LEFT])
    move (-1, 0, LEFT);
  else
    {
      last = 0;
      stand ();
    }
}

void Character::load (const char* img, int nimage)
{
  std::string e = "media/images/characters/";
  dir = 0;
  last = 0;
  e += img;
  animation.load (IMG_Load (e.c_str ()), WIDTH_MAP / 2, HEIGHT_MAP / 2,
		  nimage, 50);
  animation.mask.h /= 8;
  animation.playing = false;
  animation.mask.y = dir * (animation.img->h / 8);
}
