#ifndef INTERFACE_HH_
# define INTERFACE_HH_

# include <SDL/SDL.h>
# include <SDL/SDL_image.h>
# include <SDL/SDL_ttf.h>
# include <iostream>
# include <string>
# include <vector>

# include "interface_start.hh"

class Interface
{
public:
  Interface ();
  ~Interface ();
  void display (SDL_Surface* screen);
  void process_mouse (int x, int y);
  void process_mouse_click (int x, int y);

private:
   InterfaceStart interface_start;
};

#endif
