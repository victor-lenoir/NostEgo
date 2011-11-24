#ifndef GAME_HH_
# define GAME_HH_

# include <SDL/SDL.h>

# include "../interface/interface.hh"

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
  void process ();
  void display ();
  void set_state (int state_p);
   int get_state ();
  int w;
  int h;
  bool done;
  SDL_Surface* screen;
  Interface interface;
private:
   int state;
};

extern int g_w;
extern int g_h;

#endif
