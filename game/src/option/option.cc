#include "option.hh"
#include <SFML/Graphics.hpp>

Option::Option ()
{
  screen_w = sf::VideoMode::GetDesktopMode().Width;
  screen_h = sf::VideoMode::GetDesktopMode().Height;
  fps = 50;
}
