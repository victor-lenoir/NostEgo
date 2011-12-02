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
  SDL_Surface* tmp = 0;
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
    }
  else
  {
     input >> background_str;
     if (background_str != "none")
     {
	background_str = "media/images/maps/background/" + background_str;
	background = IMG_Load (background_str.c_str ());
	if (!background)
	   std::cerr << "Invalid background file: " << background_str << std::endl;
     }
  }

  tmp = SDL_CreateRGBSurface (SDL_SWSURFACE, WIDTH_MAP, HEIGHT_MAP, 32,0,0,0,0);

  SDL_Rect toblit;

  for (toblit.y = 0; toblit.y < HEIGHT_MAP; toblit.y += background->h)
     for (toblit.x = 0; toblit.x < WIDTH_MAP; toblit.x += background->w)
	SDL_BlitSurface (background, 0, tmp, &toblit);
  SDL_FreeSurface (background);
  background = tmp;
  if (!input.good ())
     return;

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

void Map::display_background (SDL_Surface* screen,
			      int offsetx,
			      int offsety)
{
   if (background)
    {

      SDL_Rect tmp_rect;

      tmp_rect.x = offsetx;
      tmp_rect.y = offsety;
      SDL_BlitSurface (background, 0, screen,
		       &tmp_rect);
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
		      (*it)->animation.rect.y) && (g->player->animation.rect.y + g->player->animation.rect.h -  g->yoff <
						   (*it)->animation.rect.y + (*it)->animation.rect.h))
	{
	  g->player->display (screen);
	  play = true;
	}
      (*it)->display (screen, offsetx, offsety);
    }
  if (!play)
    g->player->display (screen);
}
