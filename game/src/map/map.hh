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
  bool load_map (const char* map_path, bool display_on = true);
  void display (int offsetx, int offsety);
  void display_background (int offsetx, int offsety);
  Element* get_element_by_id(int id);
  sf::Sprite* background;
  sf::Image* img;
  std::list<Element*> elements;
};

#endif
