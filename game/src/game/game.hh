#ifndef GAME_HH_
# define GAME_HH_

# include <SFML/Graphics.hpp>
# include <SFML/Network.hpp>
# include <map>
# include <string>
# include "../interface/interface.hh"
# include "../map/map.hh"
# include "../character/character.hh"
# include "../map/element.hh"

# include "../network/network.hh"

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
  void load_map();
  void process ();
  void display ();
  void set_state (int state_p);
  int get_state ();
  bool done;
  Interface* interface;
  Map* map;

  Character* player;
  std::map<int, Character*> characters;
  sf::SocketTCP Socket;
  bool init;
private:
  int state;
};

extern Game* g;
extern bool g_display;

#endif
