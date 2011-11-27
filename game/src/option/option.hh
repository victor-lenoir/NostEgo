#ifndef OPTION_HH_
# define OPTION_HH_

# include <SDL/SDL.h>
# include <SDL/SDL_ttf.h>

# define WIDTH_MAP 1024
# define HEIGHT_MAP 768

struct Option
{
  Option ();
  int video_flags;
  int screen_w;
  int screen_h;
  int fps;
};

extern Option* opt;

#endif
