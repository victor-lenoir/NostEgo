#include "interface.hh"
//#include "../game/game.hh"

Interface::Interface ()
{
}

Interface::~Interface ()
{
}

void Interface::clean ()
{
   /*
   interface_start.clean ();
   interface_creation.clean ();
   */
}

void Interface::display ()
{
   interface_start.display ();
   /*
   switch (g->get_state())
   {
      case START:
	 interface_start.display (screen);
	 break;
      case CREATION:
         interface_creation.display (screen);
         break;
      case MAP:
	interface_debug.display (screen);
	 break;
   }
   */
}
