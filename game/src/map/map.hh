#ifndef MAP_HH_
# define MAP_HH_

# include <SDL/SDL.h>
# include <SDL/SDL_image.h>
# include <iostream>
# include <string>
# include <list>

# include "element.hh"

class Map
{
public:
  Map ();
  ~Map();
  void clean ();
  void process_keyboard (Uint8* keystate);
  void load_map (const char* map_path);
  void display (SDL_Surface* screen, int offsetx, int offsety);
  void display_background (SDL_Surface* screen,
			   int offsetx,
			   int offsety);
  SDL_Surface* background;
  std::list<Element*> elements;
};

#endif
