#include "interface_start.hh"
//#include "../game/game.hh"
#include <iostream>

void InterfaceStart::quit ()
{
   //g->app->Close();
}

void InterfaceStart::create_new_player ()
{
   //g->set_state (CREATION);
}

InterfaceStart::InterfaceStart()
{
   int y = 0;
   sf::Font* stone = new sf::Font;
   if (!stone->LoadFromFile("media/fonts/stonehenge.ttf"))
      std::cerr << "Failed to load media/fonts/stonehenge.ttf" << std::endl;
   add_hypertexte (opt->screen_w / 2, y, stone, "Create new player", 0);

   /*
  int y = 0;

   start_font = TTF_OpenFont("media/fonts/stonehenge.ttf", 55);
   if (!start_font)
      std::cout << "TTF OpenFont = " << TTF_GetError() << std::endl;

   add_image ("media/images/interface/start.png", opt->screen_w / 2, 100, true);
   y = add_hypertexte (opt->screen_w / 2, 350, start_font, "Create new player",
		       &InterfaceStart::create_new_player, this, true)->h +
     350;
   y = add_hypertexte (opt->screen_w / 2, y, start_font, "Load game", 0, this, true)->h +
     y;
   y = add_hypertexte (opt->screen_w / 2, y, start_font, "Exit", &InterfaceStart::quit,
		       this,
		       true)->h + y;
   */
}

InterfaceStart::~InterfaceStart ()
{
}
