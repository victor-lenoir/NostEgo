#ifndef MAP_HH_
# define MAP_HH_

# include <SDL/SDL.h>
# include <SDL/SDL_image.h>
# include <iostream>
# include <string>
# include <vector>

# include "element.hh"

class Map
{
public:
  Map ();
  ~Map();
  void clean ();
  void load_map (const char* map_path);
  void display (SDL_Surface* screen);

  SDL_Surface* background;
  std::vector<Element*> elements;
};

#endif
