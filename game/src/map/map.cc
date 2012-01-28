#include "map.hh"
#include <fstream>
#include "../game/game.hh"
#include "chest.hh"
#include "monster.hh"

Map::Map ()
{
  img = 0;
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
  if (img)
    {
      img_mng->free (img);
      img = 0;
    }
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


void Map::load_map (const char* map_path, int xmap_, int ymap_)
{
  std::ifstream input (map_path);
  std::string background_str;
  std::string element;
  int x;
  int y;
  std::string hash_background;

  xmap = xmap_;
  ymap = ymap_;
  clean ();
  if (!input.good ())
    background_str = "media/images/maps/background/grass.png";
  else
    {
      input >> background_str;
      background_str = "media/images/maps/background/" + background_str;
    }

  hash_background = "background_" + background_str;

  if (!img_mng->get(hash_background.c_str (), img))
    {
      sf::Image tmp;

      tmp.LoadFromFile(background_str.c_str ());
      tmp.SetSmooth(true);
      img->Create (WIDTH_MAP, HEIGHT_MAP);
      for (size_t j = 0; j < HEIGHT_MAP; j += tmp.GetHeight ())
	for (size_t i = 0; i < WIDTH_MAP; i += tmp.GetWidth ())
	  img->Copy (tmp, i, j);
      img->SetSmooth(true);
    }

  background = new sf::Sprite (*img);
  if (!background)
    std::cerr << "Invalid background file: " << background_str << std::endl;

  if (!input.good ())
     return;

  while (!input.eof())
    {
      std::string hash = map_path;
      input >> element;
      input >> x;
      input >> y;
      hash += "#" + int_to_string(x) + "#" + int_to_string(y) + "#" + element;
      /*
      if ((it = g->global_elements.find (hash)) != g->global_elements.end ())
      {
          char buffer[1024];

          input.getline (buffer, 1024);
          elements.push_back (it->second);
      }
      else
      {*/
          if (element == "chest")
            elements.push_back (new Chest (x, y, input, hash));
          else if (element[0] == '_')
            elements.push_back (new Monster (x, y, input, hash, element));
          else
            elements.push_back (new Element (element, x, y, 1));
        /*
      }*/
    }
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

void Map::display (int offsetx,
		   int offsety,
		   bool play_)
{
  bool play = play_;

  elements.sort (compare_element);
  for (std::list<Element*>::iterator it = elements.begin();
       it != elements.end (); ++it)
    {
      if ((!play)
            && (g->player->animation->GetPosition().y - g->yoff < (*it)->animation->GetPosition().y)
            && (g->player->animation->GetPosition().y + g->player->animation->GetSubRect().GetHeight() -  g->yoff <
						   (*it)->animation->GetPosition().y + (*it)->animation->GetSubRect().GetHeight()))
	{
	  g->player->display ();
	  play = true;
	}
      (*it)->display (offsetx, offsety);
    }
  if (!play)
    g->player->display ();
  for (std::map<int, Character*>::iterator it = g->characters.begin() ; it != g->characters.end(); it++)
      if ((it->second->xmap == xmap) && (it->second->ymap == ymap))
    it->second->display (offsetx, offsety);
}
