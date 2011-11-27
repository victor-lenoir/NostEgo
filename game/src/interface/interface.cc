#include "interface.hh"
#include "../game/game.hh"

Interface::Interface ()
{
}

Interface::~Interface ()
{
}

void Interface::process_keyboard (SDLKey key)
{
   switch (g->get_state())
    {
    case START:
      interface_start.process_keyboard (key);
      break;
    case CREATION:
      interface_creation.process_keyboard (key);
      break;
    }
}

void Interface::clean ()
{
   interface_start.clean ();
   interface_creation.clean ();
}

void Interface::process_mouse (int x,
			       int y)
{
   switch (g->get_state())
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
   switch (g->get_state())
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
   switch (g->get_state())
   {
      case START:
	 interface_start.display (screen);
	 break;
      case CREATION:
         interface_creation.display (screen);
         break;
   }
}
