#ifndef MAP_HH_
# define MAP_HH_

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
  void process_keyboard ();
  void load_map (const char* map_path, int xmap_, int ymap_);
  void display ();
  void display_background ();
  sf::Sprite* background;
  sf::Image* img;
  int xmap;
  int ymap;
  std::list<Element*> elements;
};

#endif
