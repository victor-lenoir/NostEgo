#include "animation.hh"
#include "../option/option.hh"
#include <iostream>

Animation::Animation ()
{
  last_process = 0;
  delay_process = 20;
  step = 0;
  img = 0;
  playing = true;
  stepping = false;
  once = false;
}

Animation::~Animation ()
{
  if (img)
    SDL_FreeSurface (img);
}

void Animation::display (SDL_Surface* screen)
{
  Uint32 curr_process;

  mask.x = step * (img->w / max_step);
  if ((rect.x + img->w > 0)
      && (rect.x < opt->screen_w) &&
      (rect.y + img->h > 0)
      && (rect.y < opt->screen_h))
  SDL_BlitSurface (img, &mask, screen, &rect);
  if ((!playing) && (!stepping) && (!once))
    return;
  stepping = false;
  if (!last_process)
    {
      last_process = SDL_GetTicks();
      return;
    }
  curr_process = SDL_GetTicks ();
  if (curr_process - last_process > delay_process)
    {
      ++step;
      if ((!once) && (step >= max_step))
	step = 0;
      else if (step >= max_step)
	{
	  --step;
	  once = false;
	}

      last_process = curr_process;
    }
}

void Animation::load (SDL_Surface* p_img,
		      int x,
		      int y,
		      int p_max_step,
		      int p_delay_process)
{
  img = p_img;
  rect.x = x;
  rect.y = y;
  mask.x = 0;
  mask.y = 0;
  mask.h = img->h;
  mask.w = img->w / p_max_step;
  max_step = p_max_step;
  rect.h = mask.h;
  rect.w = mask.w;
  delay_process = p_delay_process;
}
