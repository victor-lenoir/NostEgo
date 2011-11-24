#include "interface.hh"
#include "../game/game.hh"

Interface::Interface ()
{
   state = START;
}

Interface::~Interface ()
{
}

void Interface::process_mouse (int x,
			       int y)
{
   switch (state)
   {
      case START:
	 interface_start.process_mouse (x, y);
	 break;
   }
}
void Interface::display (SDL_Surface* screen)
{
   switch (state)
   {
      case START:
	 interface_start.display (screen);
	 break;
   }
}
