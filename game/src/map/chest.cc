#include "chest.hh"

Chest::Chest (int x, int y, std::ifstream& input, std::string hash)
  : Element ("chest", x, y)
{
  std::string object;

  animation->pause ();
  input >> object;
  set_global(hash);
  std::cout << "Creating chest containing = " << object << std::endl;
}

void Chest::process_keyboard_bottom ()
{
  //if (key[SDLK_SPACE])
  animation->play ();
}
