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
  bool load_map (const char* map_path, bool display_on = true);
  void display ();
  void display_background ();
  sf::Sprite* background;
  sf::Image* img;
  std::list<Element*> elements;
};

#endif
