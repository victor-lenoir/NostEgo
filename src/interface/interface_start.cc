#include "interface_start.hh"
#include "../game/game.hh"
#include <iostream>

extern Game* g;

void quit ()
{
   g->done = true;
}

void create_new_player ()
{
   g->set_state (CREATION);
}

InterfaceStart::InterfaceStart()
{
  int y = 0;

   start_font = TTF_OpenFont("media/fonts/stonehenge.ttf", 55);
   if (!start_font)
      std::cout << "TTF OpenFont = " << TTF_GetError() << std::endl;

   add_image ("media/images/interface/start.png", g_w / 2, 100, true);
   y = add_hypertexte (g_w / 2, 350, start_font, "Create new player", &create_new_player, true)->h + 350;
   y = add_hypertexte (g_w / 2, y, start_font, "Load game", 0, true)->h + y;
   y = add_hypertexte (g_w / 2, y, start_font, "Exit", &quit, true)->h + y;
}

InterfaceStart::~InterfaceStart ()
{
   TTF_CloseFont (start_font);
}
