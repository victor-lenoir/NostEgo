#ifndef IMAGE_HH_
# define IMAGE_HH_

typedef void (*t_func)();

struct Image
{
  Image ()
  {
    img = 0;
    img_over = 0;
    handler = 0;
    over = false;
  }
  ~Image ()
  {
  }
  SDL_Rect rect;
  t_func handler;
  bool over;
  SDL_Surface* img;
  SDL_Surface* img_over;
};
#endif
