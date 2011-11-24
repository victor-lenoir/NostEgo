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

  int state;
  int w;
  int h;
  bool done;
  SDL_Surface* screen;
  Interface interface;
};

extern int g_w;
extern int g_h;

#endif
