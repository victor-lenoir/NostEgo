#ifndef GAME_HH_
# define GAME_HH_

# include <SDL/SDL.h>

# include "../interface/interface.hh"
# include "../map/map.hh"
# include "../character/character.hh"

enum
{
   START,
   CREATION,
   MAP,
   FIGHT
};

struct Game
{
  Game ();
  ~Game ();
  void load_maps ();
  void process ();
  void display ();
  void set_state (int state_p);
  int get_state ();
  bool done;
  SDL_Surface* screen;
  Interface interface;
  Map maps[3][3];

  Character player;
  std::string world_map;
  int xmap;
  int ymap;
private:
   int state;
};

extern int g_w;
extern int g_h;

#endif
