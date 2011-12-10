#include "chest.hh"
#include "../option/option.hh"

Chest::Chest (int x, int y, std::ifstream& input, std::string hash)
  : Element ("chest", x, y)
{
  std::string object;

  animation->pause ();
  animation->once = true;
  input >> object;
  set_global(hash);
  open = false;
}

void Chest::process_keyboard_bottom ()
{
  if ((!open) && (app->GetInput().IsKeyDown (sf::Key::Space)))
  {
    animation->play ();
    open = true;
  }


}
