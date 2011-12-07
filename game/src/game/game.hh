#ifndef GAME_HH_
# define GAME_HH_

# include <SFML/Graphics.hpp>
# include <map>
# include <string>
# include "../interface/interface.hh"
//# include "../map/map.hh"
# include "../character/character.hh"
//# include "../map/element.hh"

# define MAP_BUFFER 5

enum
{
   START,
   CREATION,
   MAP,
   FIGHT
};

std::string int_to_string (int n);

struct Game
{
  Game ();
  ~Game ();
  void init_game ();
  //void load_maps ();
  void process ();
  void display ();
  void set_state (int state_p);
  int get_state ();
  bool done;
  Interface* interface;
  //Map* maps[MAP_BUFFER][MAP_BUFFER];

  Character* player;
  std::string world_map;
  int xmap;
  int ymap;
  int xoff;
  int yoff;
  bool init;
   //std::map<std::string, Element*> global_elements;
private:
  int state;
};

extern Game* g;

#endif
