#include "option.hh"
#include <SFML/Graphics.hpp>

Option::Option ()
{
  video_flags = 0;
  screen_w = sf::VideoMode::GetDesktopMode().Width;
  screen_h = sf::VideoMode::GetDesktopMode().Height;
  fps = 50;
  video_flags |= SDL_SWSURFACE |
    SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE;
}
