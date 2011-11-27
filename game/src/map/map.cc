#include "map.hh"
#include <fstream>
#include "../game/game.hh"

extern Game* g;

Map::Map ()
{
  background = 0;
}

void Map::clean ()
{
  if (background)
    {
      SDL_FreeSurface (background);
      background = 0;
    }
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

// TODO: Optimize
void Map::display_background (SDL_Surface* screen,
			      int offsetx,
			      int offsety)
{
  if (background)
    {
      SDL_Rect tmp_rect;

      for (tmp_rect.y = offsety; tmp_rect.y < offsety + HEIGHT_MAP;
           tmp_rect.y += background->h)
	for (tmp_rect.x = offsetx; tmp_rect.x < offsetx + WIDTH_MAP;
	     tmp_rect.x += background->w)
	  {
	    if ((tmp_rect.x >= 0) && (tmp_rect.x < g_w)
		&& (tmp_rect.y >= 0) && (tmp_rect.y < g_h))
	      SDL_BlitSurface (background, 0, screen,
			     &tmp_rect);
	  }
    }
}

void Map::display (SDL_Surface* screen,
		   int offsetx,
		   int offsety)
{
  bool play = false;

  if (g->get_state() != MAP)
    return;

  display_background (screen, offsetx, offsety);
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
      (*it)->display (screen, offsetx, offsety);
    }
  if (!play)
    g->player.display (screen);
}
