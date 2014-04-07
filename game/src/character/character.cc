#include "character.hh"
#include "../game/game.hh"
#include <iostream>

void Character::keyboard_pressed(int key) {
  keydowns[key] = true;
}

void Character::keyboard_released(int key) {
  keydowns[key] = false;
}

void Character::process(Map* m, std::map<std::string, std::vector<Client*> >& clients_per_map,
                        std::map<std::string, Map*>& maps) {
  // Process key_board for * element
  for (std::list<Element*>::iterator it = m->elements.begin(); it != m->elements.end(); ++it) {
    (*it)->process_keyboard_general(this);
  }
  process_keyboard(m, clients_per_map, maps);
}

void Character::display (int offsetx, int offsety)
{
  if (!animation) {
    sf::Image* img;
    if (!img_mng->get ("media/images/characters/healer.png", img))
    {
      img->LoadFromFile("media/images/characters/healer.png");
      img->SetSmooth(true);
    }
    animation = new ImgAnim (0.05, img, 8, 8);
    animation->pause ();
    animation->once = true;
  }
  animation->SetX(x + offsetx);
  animation->SetY(y + offsety);
  animation->setAnimRow(dir);
  app->Draw(*animation);
}

int Character::get_speed ()
{
  return (400 / (1 + 40));
}

void Character::move (float xpar,
                      float ypar,
                      int dir_p,
                      Map* m,
                      std::map<std::string, std::vector<Client*> >& clients_per_map,
                      std::map<std::string, Map*>& maps)
{
  float deltax = get_speed ();
  float deltay = get_speed ();

  deltax *= xpar;
  deltay *= ypar;
  x += deltax;
  y += deltay;
  bool changemap = (x >= WIDTH_MAP) || (x < 0) || (y >= HEIGHT_MAP) || (y < 0);
  Client* toreadd = 0;

  if (changemap) {
    for (std::vector<Client*>::iterator it = on_map->begin() ; it != on_map->end(); ++it) {
      if ((*it)->c->id == id) {
        toreadd = (*it);
        on_map->erase(it);
        break;
      }
    }
    broadcast_maps(m);
  }

  if (x >= WIDTH_MAP) {
    x = 1;
    xmap++;
  }
  else if (x < 0) {
    x = WIDTH_MAP - 1;
    xmap--;
  }
  else if (y >= HEIGHT_MAP) {
    y = 1;
    ymap++;
  }
  else if (y < 0) {
    y = HEIGHT_MAP - 1;
    ymap--;
  }

  if (changemap) {
    if (clients_per_map.count(hash_map()) == 0)
      clients_per_map.insert(std::pair<std::string, std::vector<Client*> >(hash_map(), std::vector<Client*>()));
    clients_per_map[hash_map()].push_back(toreadd);
    load_characters(&clients_per_map[hash_map()]);
    broadcast_maps(maps[hash_map()]);
  }
  dir = dir_p;
}

bool Character::is_key_down(int key) {
  return keydowns[key];
}
void Character::process_keyboard (Map* m, std::map<std::string, std::vector<Client*> >& clients_per_map, std::map<std::string, Map*>& maps)
{
  bool up = is_key_down(sf::Key::Up);
  bool down = is_key_down(sf::Key::Down);
  bool left = is_key_down(sf::Key::Left);
  bool right = is_key_down(sf::Key::Right);


  if (up && canup && right && canright)
    move (SQRT2, -SQRT2, UP_RIGHT, m, clients_per_map, maps);
  else if (down && candown && right && canright)
    move (SQRT2, SQRT2, DOWN_RIGHT, m, clients_per_map, maps);
  else if (up && canup && left && canleft)
    move (-SQRT2, -SQRT2, UP_LEFT, m, clients_per_map, maps);
  else if (down && candown && left && canleft)
    move (-SQRT2, SQRT2, DOWN_LEFT, m, clients_per_map, maps);
  else if (up && canup)
    move (0, -1, UP, m, clients_per_map, maps);
  else if (down && candown)
    move (0, 1, DOWN, m, clients_per_map, maps);
  else if (right && canright)
    move (1, 0, RIGHT, m, clients_per_map, maps);
  else if (left && canleft)
    move (-1, 0, LEFT, m, clients_per_map, maps);
  else
  {
    if (up && right)
      dir = UP_RIGHT;
    else if (down && right)
      dir = DOWN_RIGHT;
    else if (up && left)
      dir = UP_LEFT;
    else if (down && left)
      dir = DOWN_LEFT;
    else if (up)
      dir = UP;
    else if (down)
      dir = DOWN;
    else if (right)
      dir = RIGHT;
    else if (left)
      dir = LEFT;
  }
  canright = true;
  canleft = true;
  candown = true;
  canup = true;

  if (up || down || left || right)
    share_position();
}

void Character::share_position()
{
  sf::Packet Packet;

  Packet << NETWORK_CHARACTER_MOVE
         << (int)id
         << (int)x
         << (int)y
         << (int)dir;
  for (size_t k = 0; k < on_map->size(); ++k) {
    (*on_map)[k]->socket.Send(Packet);
  }
}

void Character::broadcast_local(sf::Packet& sPacket){
  for (size_t k = 0; k < on_map->size(); ++k) {
    (*on_map)[k]->socket.Send(sPacket);
  }
}

void Character::broadcast_maps(Map* m) {
  sf::Packet sPacket;

  sPacket << NETWORK_NEW_MAP;
  sPacket << world_map << xmap << ymap;
  sPacket << (int)on_map->size();

  for (size_t k = 0; k < on_map->size(); ++k) {
    sPacket << (*on_map)[k]->c->id << (*on_map)[k]->c->x << (*on_map)[k]->c->y << (*on_map)[k]->c->dir;
  }
  //sPacket << (int)map
  for (std::list<Element*>::iterator it = m->elements.begin();
       it != m->elements.end (); ++it)
  {
    (*it)->update(sPacket);
  }
  sPacket << NETWORK_EOF;
  // SEND ALL CHARACTERS ON CURRENT MAP.
  // AND ALL ELEMENTS
  broadcast_local(sPacket);
}

std::string Character::hash_map()
{
  return world_map + "#" + int_to_string(xmap) + "#" + int_to_string(ymap);
}
void Character::load_characters(std::vector<Client*>* on_map_) {
  on_map = on_map_;
}


void Character::init_chara() {
  animation = 0;
  id = -1;
  dir = DOWN;
  x = WIDTH_MAP / 2;
  y = HEIGHT_MAP / 2;
  world_map = "test";
  xmap = 0;
  ymap = 0;
  width = 32;
  height = 64;
}
Character::Character ()
{
  init_chara();
}

Character::Character(std::string world_map_, int xmap_, int ymap_, int x_, int y_, int dir_)
{
  init_chara();
  world_map = world_map_;
  xmap = xmap_;
  ymap = ymap_;
  x = x_;
  y = y_;
  dir = dir_;
}

Character::~Character ()
{
  if (animation) {
    delete animation;
  }
}
