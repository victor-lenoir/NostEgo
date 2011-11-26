#include "map.hh"
#include <fstream>
#include "../game/game.hh"

extern Game* g;

Map::Map ()
{
  background = 0;
  load_map ("media/maps/test0-0");
}

void Map::clean ()
{
  for (size_t i = 0; i < elements.size (); ++i)
    delete elements[i];
}

Map::~Map ()
{
  clean ();
}
void Map::load_map (const char* map_path)
{
  std::ifstream input (map_path);
  std::string background_str;
  std::string element;
  int x;
  int y;

  clean ();
  if (!input.good ())
    {
      std::cerr << "Invalid map file: " << map_path << std::endl;
      return;
    }
  input >> background_str;
  if (background_str != "none")
    background = IMG_Load (background_str.c_str ());
  while (!input.eof())
    {
      input >> element;
      input >> x;
      input >> y;
      elements.push_back (new Element (element, x, y));
    }
}

void Map::display (SDL_Surface* screen)
{
  if (g->get_state() != MAP)
    return;
  for (size_t i = 0; i < elements.size (); ++i)
    {
      elements[i]->animations[0]->display (screen);
      elements[i]->animations[1]->display (screen);
    }
}
