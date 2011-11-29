#include "chest.hh"

Chest::Chest (int x, int y, std::ifstream& input, std::string hash)
  : Element ("chest", x, y)
{
  std::string object;

  animation.playing = false;
  input >> object;
  set_global(hash);
  std::cout << "Creating chest containing = " << object << std::endl;
}

void Chest::process_keyboard_bottom (Uint8* key)
{
  if (key[SDLK_UP])
    animation.once = true;
}
