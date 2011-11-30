#include "map.hh"
#include <fstream>
#include "../game/game.hh"
#include "chest.hh"

Map::Map ()
{
  background = 0;
}

void Map::process_keyboard (Uint8* keystate)
{
   for (std::list<Element*>::iterator it = elements.begin();
	it != elements.end (); ++it)
      (*it)->process_keyboard_general (keystate);
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
    {
      if (!(*it)->global)
	delete (*it);
    }
  elements.clear ();
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
       background_str = "media/images/maps/background/grass.png";
       background = IMG_Load (background_str.c_str ());
       if (!background)
	  std::cerr << "Invalid background file: " << background_str << std::endl;
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
      std::string hash = map_path;
      input >> element;
      input >> x;
      input >> y;
      hash += int_to_string(x) + "#" + int_to_string(y) + "#" + element;
      std::map<std::string, Element*>::iterator it;

      if ((it = g->global_elements.find (hash)) != g->global_elements.end ())
      {
	  char buffer[1024];

	  input.getline (buffer, 1024);
	  elements.push_back (it->second);
	}
      else
	{
	  if (element == "chest")
	    elements.push_back (new Chest (x, y, input, hash));
	  else
	    elements.push_back (new Element (element, x, y));
	}

    }
}

static bool compare_element (Element* e1,
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

      for (int defy = offsety; defy < offsety + HEIGHT_MAP;
           defy += background->h)
	for (int defx = offsetx; defx < offsetx + WIDTH_MAP;
	     defx += background->w)
	  {
	    tmp_rect.x = defx;
	    tmp_rect.y = defy;
	    if ((tmp_rect.x + background->w > 0)
		&& (tmp_rect.x < opt->screen_w) &&
		(tmp_rect.y + background->h > 0)
                && (tmp_rect.y < opt->screen_h))
	    SDL_BlitSurface (background, 0, screen,
			     &tmp_rect);
	  }
    }
}

void Map::display (SDL_Surface* screen,
		   int offsetx,
		   int offsety,
		   bool play_)
{
  bool play = play_;

  elements.sort (compare_element);
  for (std::list<Element*>::iterator it = elements.begin();
       it != elements.end (); ++it)
    {
      if ((!play) && (g->player->animation.rect.y - g->yoff <
		      (*it)->animation.rect.y))
	{
	  g->player->display (screen);
	  play = true;
	}
      (*it)->display (screen, offsetx, offsety);
    }
  if (!play)
    g->player->display (screen);
}
