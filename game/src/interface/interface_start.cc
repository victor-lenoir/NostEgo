#include "interface_start.hh"
#include "../game/game.hh"
#include <iostream>

void InterfaceStart::quit ()
{
  app->Close();
}

void InterfaceStart::create_new_player ()
{
  g->set_state (CREATION);
}

InterfaceStart::InterfaceStart()
{
   int y = 100;
   stone = new sf::Font;
   if (!stone->LoadFromFile("media/fonts/stonehenge.ttf"))
      std::cerr << "Failed to load media/fonts/stonehenge.ttf" << std::endl;
   y += add_animation (opt->screen_w / 2, y, 1.0, 1, 1, "media/images/interface/start.png", this, 0, true).GetHeight ();
   y += 100;
   y += add_hypertexte (opt->screen_w / 2, y, stone, "Create new player", this, &InterfaceStart::create_new_player, true).GetHeight ();
   y += add_hypertexte (opt->screen_w / 2, y, stone, "Load game", this, 0, true).GetHeight ();
   y += add_hypertexte (opt->screen_w / 2, y, stone, "Exit", this, &InterfaceStart::quit, true).GetHeight ();
}

InterfaceStart::~InterfaceStart ()
{
  delete stone;
}
