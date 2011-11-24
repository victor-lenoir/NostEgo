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
   (void)x;
   (void)y;
   //interface_start.process_mouse (x, y);
}
void Interface::display (SDL_Surface* screen)
{
   interface_start.display (screen);
}
