#include "interface.hh"
#include "../game/game.hh"

Interface::Interface ()
{
}

Interface::~Interface ()
{
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

void Interface::process_mouse_move (int x,
				    int y)
{
  switch (g->get_state())
    {
    case START:
      interface_start.process_mouse_move (x, y);
      break;
    case CREATION:
      interface_creation.process_mouse_move (x, y);
      break;
    }
}

void Interface::clean ()
{
}

void Interface::display ()
{
   switch (g->get_state())
   {
      case START:
	 interface_start.display ();
	 break;
      case CREATION:
         interface_creation.display ();
         break;
      case MAP:
	interface_debug.display ();
	 break;
   }
}
