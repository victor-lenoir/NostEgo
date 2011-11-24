#include "interface.hh"
#include "../game/game.hh"

extern Game* g;
Interface::Interface ()
{
}

Interface::~Interface ()
{
}

void Interface::process_mouse (int x,
			       int y)
{
   switch (g->state)
   {
      case START:
	 interface_start.process_mouse (x, y);
	 break;
      case CREATION:
	 interface_creation.process_mouse (x, y);
	 break;
   }
}

void Interface::process_mouse_click (int x,
                               int y)
{
   switch (g->state)
   {
      case START:
         interface_start.process_mouse_click (x, y);
         break;
      case CREATION:
	 interface_creation.process_mouse_click (x, y);
	 break;
   }
}

void Interface::display (SDL_Surface* screen)
{
   switch (g->state)
   {
      case START:
	 interface_start.display (screen);
	 break;
      case CREATION:
         interface_creation.display (screen);
         break;
   }
}
