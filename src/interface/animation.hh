#ifndef ANIMATION_HH_
# define ANIMATION_HH_

struct Animation
{
  SDL_Surface* img;
  SDL_Rect rect;
  SDL_Rect mask;
};
#endif
