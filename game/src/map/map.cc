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
  for (std::list<Element*>::iterator it = elements.begin();
       it != elements.end (); ++it)
    delete (*it);
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
    {
      background_str = "media/images/maps/background/" + background_str;
      background = IMG_Load (background_str.c_str ());
      if (!background)
	std::cerr << "Invalid background file: " << background_str << std::endl;
    }
  while (!input.eof())
    {
      input >> element;
      input >> x;
      input >> y;
      elements.push_back (new Element (element, x, y));
    }
}

bool compare_element (Element* e1,
		      Element* e2)
{
  return (e1->animation.rect.y < e2->animation.rect.y);
}

void Map::display (SDL_Surface* screen)
{
  bool play = false;

  if (g->get_state() != MAP)
    return;

  if (background)
    {
      // TO OPTIMIZE: create a big background

      SDL_Rect tmp_rect;

      for (tmp_rect.y = 0; tmp_rect.y < g_h;
	   tmp_rect.y += background->h)
      for (tmp_rect.x = 0; tmp_rect.x < g_w;
	   tmp_rect.x += background->w)
	{

	  SDL_BlitSurface (background, NULL, screen,
			   &tmp_rect);
	}
    }
  elements.sort (compare_element);
  for (std::list<Element*>::iterator it = elements.begin();
       it != elements.end (); ++it)
    {
      if ((!play) && (g->player.animation.rect.y <
		      (*it)->animation.rect.y))
	{
	  g->player.display (screen);
	  play = true;
	}
      (*it)->animation.display (screen);
    }
  if (!play)
    g->player.display (screen);
}
