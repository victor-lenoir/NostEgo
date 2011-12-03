#include "character.hh"
#include "../game/game.hh"
#include <iostream>
#include "../map/map.hh"

void Character::display (SDL_Surface* screen)
{
  animation.display (screen);
}

int Character::get_speed ()
{
   Uint32 curr = SDL_GetTicks ();

  if ((!speed_init) && (last))
  {
     speed_init = true;
     speed = (curr - last) / 3;
     last = curr;
  }
  else if (!speed_init)
     last = curr;
  return speed;
}

void Character::refresh_map ()
{
  if (animation.rect.x - g->xoff > WIDTH_MAP)
    {
      g->xoff += WIDTH_MAP;
      ++g->xmap;
      g->load_maps ();
    }
  if (animation.rect.x - g->xoff < 0)
    {
      g->xoff -= WIDTH_MAP;
      --g->xmap;
      g->load_maps ();
    }
  if (animation.rect.y - g->yoff > HEIGHT_MAP)
    {
      g->yoff += HEIGHT_MAP;
      ++g->ymap;
      g->load_maps ();
    }
  if (animation.rect.y - g->yoff < 0)
    {
      g->yoff -= HEIGHT_MAP;
      --g->ymap;
      g->load_maps ();
    }
}

void Character::move_player (int deltax,
			     int deltay)
{
  if ((int)deltax > 0)
    {
      if ((int)animation.rect.x > 3 * opt->screen_w / 4)
        g->xoff -= (int)deltax;
      else
        animation.rect.x += (int)deltax;
    }
  else
    {
      if ((int)animation.rect.x < opt->screen_w / 4)
        g->xoff -= (int)deltax;
      else
        animation.rect.x += (int)deltax;
    }

  if ((int)deltay > 0)
    {
      if ((int)animation.rect.y > 3 * opt->screen_h / 4)
        g->yoff -= (int)deltay;
      else
        animation.rect.y += (int)deltay;
    }
  else
    {
      if ((int)animation.rect.y < opt->screen_h / 4)
        g->yoff -= (int)deltay;
      else
        animation.rect.y += (int)deltay;
    }
}

void Character::move (float x,
		      float y,
		      int dir_p)
{
  float deltax = get_speed ();
  float deltay = get_speed ();

  deltax *= x;
  deltay *= y;

  dir = dir_p;

  move_player (deltax, deltay);
  refresh_map ();
  speed_init = false;
  animation.stepping = true;
  animation.mask.y = dir * (animation.img->h / 8);
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

  if (keystate[SDLK_UP] && canup && keystate[SDLK_RIGHT] && canright)
    move (SQRT2, -SQRT2, UP_RIGHT);
  else if (keystate[SDLK_DOWN] && candown && keystate[SDLK_RIGHT] && canright)
    move (SQRT2, SQRT2, DOWN_RIGHT);
  else if (keystate[SDLK_UP] && canup && keystate[SDLK_LEFT] && canleft)
    move (-SQRT2, -SQRT2, UP_LEFT);
  else if (keystate[SDLK_DOWN] && candown && keystate[SDLK_LEFT] && canleft)
    move (-SQRT2, SQRT2, DOWN_LEFT);
  else if (keystate[SDLK_UP] && canup)
    move (0, -1, UP);
  else if (keystate[SDLK_DOWN] && candown)
    move (0, 1, DOWN);
  else if (keystate[SDLK_RIGHT] && canright)
    move (1, 0, RIGHT);
  else if (keystate[SDLK_LEFT] && canleft)
    move (-1, 0, LEFT);
  else
    {
      last = 0;
      stand ();
    }
  canright = true;
  canleft = true;
  candown = true;
  canup = true;
}

void Character::load (const char* img, int nimage)
{
  std::string e = "media/images/characters/";

  speed = 0;
  speed_init = false;
  last = 0;
  canup = true;
  dir = 0;
  e += img;
  animation.load (IMG_Load (e.c_str ()), WIDTH_MAP / 2, HEIGHT_MAP / 2,
		  nimage, 50);
  animation.mask.h /= 8;
  animation.playing = false;
  animation.mask.y = dir * (animation.img->h / 8);
}
