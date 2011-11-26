#ifndef ANIMATION_HH_
# define ANIMATION_HH_

# include <SDL/SDL.h>

struct Animation
{
  void display (SDL_Surface* screen);
  void load (SDL_Surface* p_img,
	     int x,
	     int y,
	     int p_max_step,
	     int p_delay_process);
  Animation ();
  ~Animation ();

  bool playing;
  Uint32 delay_process;
  Uint32 last_process;
  int step;
  int max_step;
  SDL_Surface* img;
  SDL_Rect rect;
  SDL_Rect mask;
};
#endif
