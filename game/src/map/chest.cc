#include "chest.hh"
#include "../option/option.hh"
#include <game/game.hh>

Chest::Chest (int x_, int y_, std::ifstream& input)
  : Element ("chest", x_, y_, 1)
{
  stop_animation = true;
  input >> object;
  open = false;
}


