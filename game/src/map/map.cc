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

bool Map::load_map (const char* map_path, bool display_on)
{
  std::ifstream input (map_path);
  std::string background_str;
  std::string element;
  int x;
  int y;
  std::string hash_background;

  clean ();
  if (!input.good ())
  {
    background_str = "media/images/maps/background/grass.png";
  }
  else
  {
    input >> background_str;
    background_str = "media/images/maps/background/" + background_str;
  }

  hash_background = "background_" + background_str;
  if (display_on) {
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
  }
  if (!input.good ())
    return false;
  int cid = 0;

  while (!input.eof())
  {
    input >> element;
    input >> x;
    input >> y;
    if (element == "chest")
      elements.push_back (new Chest (x, y, input, cid));
    else if (element[0] == '_')
      elements.push_back (new Monster (x, y, input, element, cid));
    else
      elements.push_back (new Element (element, x, y, 1, cid));
    cid++;
  }
  return true;
}

static bool compare_element (Element* e1,
                             Element* e2)
{
  return (e1->y < e2->y);
}

Element* Map::get_element_by_id(int id) {
  for (std::list<Element*>::iterator it = elements.begin();
       it != elements.end (); ++it)
  {
    if ((*it)->id == id) return (*it);
  }
  return 0;
}
  
void Map::display_background ()
{
  app->Draw (*background);
}

void Map::display ()
{
  elements.sort (compare_element);
  for (std::list<Element*>::iterator it = elements.begin();
       it != elements.end (); ++it)
  {
    (*it)->display ();
  }
  for (std::map<int, Character*>::iterator it = g->characters.begin() ; it != g->characters.end(); it++)
    it->second->display();
}
