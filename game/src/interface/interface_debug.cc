#include "interface_debug.hh"
#include "../game/game.hh"
#include <iostream>

void InterfaceDebug::display ()
{
  texts[0].first->SetText ("FPS = " + int_to_string (opt->curr_fps));
  BaseInterface<InterfaceDebug>::display ();
}

InterfaceDebug::InterfaceDebug()
{
  int y = 0;

  stone = new sf::Font;
  if (!stone->LoadFromFile("media/fonts/stonehenge.ttf"))
    std::cerr << "Failed to load media/fonts/stonehenge.ttf" << std::endl;
  y += add_hypertexte (opt->screen_w / 2, y, stone, "FPS = UNDEF", this, 0, true).GetHeight ();
}

InterfaceDebug::~InterfaceDebug ()
{
  delete stone;
}
