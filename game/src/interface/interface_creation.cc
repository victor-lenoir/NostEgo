#include "interface_creation.hh"
#include "../game/game.hh"
#include <iostream>

void InterfaceCreation::previous ()
{
   g->set_state (START);
}

void InterfaceCreation::confirm ()
{
   std::string name = inputs[0]->text;

   g->set_state (MAP);
}

InterfaceCreation::InterfaceCreation()
{
  int y = 0;

   creation_font = TTF_OpenFont("media/fonts/stonehenge.ttf", 55);
   if (!creation_font)
      std::cout << "TTF OpenFont = " << TTF_GetError() << std::endl;

   add_image ("media/images/interface/start.png", WIDTH_MAP / 2, 100, true);
   y = 350;
   input_font = TTF_OpenFont("media/fonts/stonehenge.ttf", 30);
   add_input (WIDTH_MAP / 2 - 50, y + 20, 300, 40, input_font);

   y = add_hypertexte (WIDTH_MAP / 2 - 160, y, creation_font, "Name:", 0, this,
		       false)->h + y + 30;
   y = add_hypertexte (WIDTH_MAP / 2, y, creation_font, "Confirm",
		       &InterfaceCreation::confirm, this, true)->h + y;
   y = add_hypertexte (WIDTH_MAP / 2, y, creation_font, "Back",
		       &InterfaceCreation::previous, this, true)->h + y;
}

InterfaceCreation::~InterfaceCreation ()
{
  TTF_CloseFont (creation_font);
  TTF_CloseFont (input_font);
}
