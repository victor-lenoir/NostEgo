#ifndef INTERFACE_HH_
# define INTERFACE_HH_

# include <SDL/SDL.h>
# include <SDL/SDL_image.h>
# include <SDL/SDL_ttf.h>
# include <iostream>
# include <string>
# include <vector>

# include "interface_start.hh"

# define MAX_IM	5

enum
{
  START,
  CREATION,
  MAP,
  FIGHT
};

class Interface
{
public:
  Interface ();
  ~Interface ();
  void display (SDL_Surface* screen);
  void process_mouse (int x, int y);

private:
   InterfaceStart interface_start;
   int state;
};

#endif
