#include "chest.hh"

Chest::Chest (int x, int y, std::string object)
  : Element ("chest", x, y)
{
  animation.playing = false;
  std::cout << "Creating chest containing = " << object << std::endl;
}

void Chest::process_keyboard_bottom (Uint8* key)
{
  if (key[SDLK_UP])
    animation.once = true;
}
