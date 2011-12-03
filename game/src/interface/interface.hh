#ifndef INTERFACE_HH_
# define INTERFACE_HH_

# include <iostream>
# include <string>
# include <map>
# include <vector>

# include "interface_start.hh"
//# include "interface_creation.hh"
//# include "interface_debug.hh"

# include <SDL/SDL.h>

class Interface
{
public:
  Interface ();
  ~Interface ();
  void display ();
  void process_mouse (int x, int y);
  void process_mouse_click (int x, int y);
  void process_keyboard (SDLKey key);
  void clean ();

  InterfaceStart interface_start;
   //InterfaceCreation interface_creation;
   //InterfaceDebug interface_debug;
};

#endif
