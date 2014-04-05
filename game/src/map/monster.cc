#include "monster.hh"
#include "../option/option.hh"
#include <iostream>
#include "../game/game.hh"

enum
{
  MONSTER_LEFT,
  MONSTER_DOWN,
  MONSTER_UP,
  MONSTER_RIGHT
};

Monster::Monster (int x_, int y_, std::ifstream& input, std::string element)
  : Element (element, x_, y_, 8)
{
  dead = false;
  (void)input;
  dir = MONSTER_LEFT;
  refresh_dir();
  state = STANDING;
}

void Monster::attack (int dir_p)
{
    if ((state == STANDING) || (state == MOVING) || (state == RUNNING))
    {
        dir = dir_p;
        state = ATTACKING;
        refresh_dir ();
    }
}

void Monster::die ()
{
  if (!dead) {
    state = DYING;
    refresh_dir ();
    dead = true;
  }
}
void Monster::refresh_dir ()
{
}

void Monster::AI ()
{
}

void Monster::move (int dir_p)
{
  (void)dir_p;
}

void Monster::hit (int deg)
{
  (void)deg;
  die ();
}

void Monster::state_manage ()
{
}
void Monster::process_keyboard_bottom ()
{
    if (app->GetInput().IsKeyDown (sf::Key::Space))
        hit (12);
    attack (MONSTER_DOWN);
}

void Monster::process_keyboard_top ()
{
    if (app->GetInput().IsKeyDown (sf::Key::Space))
        hit (12);
    attack (MONSTER_UP);
}

void Monster::process_keyboard_left ()
{
    if (app->GetInput().IsKeyDown (sf::Key::Space))
        hit (12);
    attack (MONSTER_LEFT);
}

void Monster::process_keyboard_right ()
{
    if (app->GetInput().IsKeyDown (sf::Key::Space))
        hit (12);
    attack (MONSTER_RIGHT);
}

void Monster::process_keyboard ()
{
    state_manage();
    AI ();
    refresh_dir ();
}
