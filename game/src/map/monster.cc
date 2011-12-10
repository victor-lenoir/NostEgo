#include "monster.hh"
#include "../option/option.hh"
#include <iostream>

Monster::Monster (int x, int y, std::ifstream& input, std::string hash, std::string element)
  : Element (element, x, y, 8)
{
  animation->pause ();
  dir = 2;
  refresh_dir();
  set_global(hash);
}

void Monster::attack ()
{

    animation->FlipX(dir % 2);
    if (dir < 2)
        animation->setAnimRow(4);
    else
        animation->setAnimRow(5);
    animation->loop(false);
    animation->reset();
    animation->play();
}

void Monster::die ()
{
    animation->FlipX(dir % 2);
     if (dir < 2)
        animation->setAnimRow(6);
    else
        animation->setAnimRow(7);
    animation->loop(false);
    animation->reset();
    animation->play();
    animation->once = true;
    dead = true;
}
void Monster::refresh_dir ()
{
    animation->FlipX(dir % 2);
    if (dir < 2)
        animation->setAnimRow(0);
    else
        animation->setAnimRow(1);
}
void Monster::process_keyboard ()
{
    if ((app->GetInput().IsKeyDown (sf::Key::Right)))
        {
           dir = 1;
           refresh_dir();
        }
     if ((app->GetInput().IsKeyDown (sf::Key::Left)))
        {
           dir = 0;
           refresh_dir();
        }
       if ((app->GetInput().IsKeyDown (sf::Key::Up)))
        {
           dir = 2;
           refresh_dir();
        }
     if ((app->GetInput().IsKeyDown (sf::Key::Down)))
        {
           dir = 3;
           refresh_dir();
        }
    if ((app->GetInput().IsKeyDown (sf::Key::Space)))
        die ();
}
