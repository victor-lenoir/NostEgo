#ifndef ELEMENT_HH_
# define ELEMENT_HH_

# include <string>
# include <iostream>
# include <fstream>
# include "../draw/animation.hh"

# include <vector>
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>

class Element
{
public:
  Element (std::string element, int x, int y);
  ~Element ();
  void display (SDL_Surface* screen,
		int offsetx,
		int offsety);
  Animation animation;
};
#endif
