#include "option.hh"

Option::Option ()
{
  video_flags = 0;
  SDL_Init (SDL_INIT_VIDEO);
  TTF_Init ();
  screen_w = SDL_GetVideoInfo()->current_w;
  screen_h = SDL_GetVideoInfo()->current_h;
  fps = 100;
  video_flags |= SDL_FULLSCREEN | SDL_SWSURFACE |
    SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE;
}
