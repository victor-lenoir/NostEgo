#include "interface_creation.hh"
#include "../game/game.hh"
#include <iostream>

extern Game* g;

void previous ()
{
  g->state = START;
}

void confirm ()
{
  // CREATE PERSO WITH RIGHT DATA
  g->state = MAP;
}

InterfaceCreation::InterfaceCreation()
{
  int y = 0;

   creation_font = TTF_OpenFont("media/fonts/stonehenge.ttf", 55);
   if (!creation_font)
      std::cout << "TTF OpenFont = " << TTF_GetError() << std::endl;

   add_image ("media/images/interface/start.png", g_w / 2, 100, true);
   y = 350;
   y = add_hypertexte (g_w / 2 - 200, y, creation_font, "Name:", 0, false)->h + y + 30;
   y = add_hypertexte (g_w / 2, y, creation_font, "Confirm", &confirm, true)->h + y;
   y = add_hypertexte (g_w / 2, y, creation_font, "Back", &previous, true)->h + y;
}

InterfaceCreation::~InterfaceCreation ()
{
  TTF_CloseFont (creation_font);
}
