#include "interface_creation.hh"
#include "../game/game.hh"
#include <iostream>

void InterfaceCreation::previous ()
{
   g->set_state (START);
}

void InterfaceCreation::confirm ()
{
   g->set_state (MAP);
}

InterfaceCreation::InterfaceCreation()
{
  int y = 100;
  stone = new sf::Font;
  if (!stone->LoadFromFile("media/fonts/stonehenge.ttf"))
    std::cerr << "Failed to load media/fonts/stonehenge.ttf" << std::endl;
  y += add_animation (opt->screen_w / 2, y, 1, 1, "media/images/interface/start.png", this, 0, true).GetHeight ();
  y += 100;
  y += add_hypertexte (opt->screen_w / 2, y, stone, "Confirm", this, &InterfaceCreation::confirm, true).GetHeight ();
  y += add_hypertexte (opt->screen_w / 2, y, stone, "Back", this, &InterfaceCreation::previous, true).GetHeight ();
}

InterfaceCreation::~InterfaceCreation ()
{
  delete stone;
}
