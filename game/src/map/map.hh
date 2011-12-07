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
  void load_map (const char* map_path);
  void display (int offsetx, int offsety, bool play_);
  void display_background (int offsetx,
			   int offsety);
  sf::Sprite* background;
  sf::Image* img;
  std::list<Element*> elements;
};

#endif
