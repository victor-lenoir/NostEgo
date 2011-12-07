#include "map.hh"
#include <fstream>
#include "../game/game.hh"
#include "chest.hh"

Map::Map ()
{
  background = 0;
}

void Map::process_keyboard ()
{
   for (std::list<Element*>::iterator it = elements.begin();
	it != elements.end (); ++it)
      (*it)->process_keyboard_general ();
}
void Map::clean ()
{
  if (background)
    {
      delete background;
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
  sf::Image* img;
  sf::Image* tmp;
  clean ();
  if (!input.good ())
    background_str = "media/images/maps/background/grass.png";
  else
    {
      input >> background_str;
      background_str = "media/images/maps/background/" + background_str;
    }

  tmp = new sf::Image;
  tmp->LoadFromFile(background_str.c_str ());
  tmp->SetSmooth(true);
  img = new sf::Image;
  img->Create (WIDTH_MAP, HEIGHT_MAP);
  for (size_t y = 0; y < HEIGHT_MAP; y += tmp->GetHeight ())
    for (size_t x = 0; x < WIDTH_MAP; x += tmp->GetWidth ())
      img->Copy (*tmp, x, y);
  img->SetSmooth(true);
  delete tmp;
  background = new sf::Sprite (*img);
  if (!background)
    std::cerr << "Invalid background file: " << background_str << std::endl;

  if (!input.good ())
     return;
  /*
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
  */
}

static bool compare_element (Element* e1,
			     Element* e2)
{
  return (e1->animation->GetPosition().y < e2->animation->GetPosition().y);
}

void Map::display_background (int offsetx,
			      int offsety)
{

  background->Move (offsetx, offsety);
  app->Draw (*background);
  background->Move (-offsetx, -offsety);
}
/*
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
*/
