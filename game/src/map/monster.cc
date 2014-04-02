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

Monster::Monster (int x, int y, std::ifstream& input, std::string hash, std::string element)
  : Element (element, x, y, 8)
{
  dead = false;
  (void)input;
  animation->pause ();
  dir = MONSTER_LEFT;
  refresh_dir();
  state = STANDING;
  set_global(hash);
}

void Monster::attack (int dir_p)
{
    if ((state == STANDING) || (state == MOVING) || (state == RUNNING))
    {
        dir = dir_p;
        state = ATTACKING;
        refresh_dir ();
        animation->loop(false);
        animation->once = false;
        animation->reset();
        animation->play();
    }
}

void Monster::die ()
{
  if (!dead) {
    state = DYING;
    refresh_dir ();
    animation->loop(false);
    animation->once = true;
    animation->reset();
    animation->play();
    dead = true;
  }
}
void Monster::refresh_dir ()
{
    animation->FlipX(dir % 2);
    if (state == STANDING)
        animation->setAnimRow(0 + (dir >= 2));
    else if (state == MOVING)
        animation->setAnimRow(0 + (dir >= 2));
    else if (state == RUNNING)
        animation->setAnimRow(2 + (dir >= 2));
    else if (state == ATTACKING)
        animation->setAnimRow(4 + (dir >= 2));
     else if (state == DYING)
        animation->setAnimRow(6 + (dir >= 2));
}

void Monster::AI ()
{
    bool okay = false;
    if ((g->player->animation->GetPosition().x - g->xoff + g->player->animation->GetSubRect().GetWidth() >= animation->GetPosition().x) &&
      (g->player->animation->GetPosition().x - g->xoff <= animation->GetPosition().x + animation->GetSubRect().GetWidth()))
        {
            okay = true;
        }
    else if (animation->GetPosition().x > g->player->animation->GetPosition().x - g->xoff )
        move (MONSTER_LEFT);
    else
        move (MONSTER_RIGHT);
    if (okay)
    {
        if ((g->player->animation->GetPosition().y - g->yoff + g->player->animation->GetSubRect().GetHeight() / 1.5 >= animation->GetPosition().y) &&
        (g->player->animation->GetPosition().y - g->yoff + g->player->animation->GetSubRect().GetHeight() / 1.5 <= animation->GetPosition().y + animation->GetSubRect().GetHeight()))
      {

      }
      else if (animation->GetPosition().y > g->player->animation->GetPosition().y - g->yoff )
        move (MONSTER_UP);
    else
        move (MONSTER_DOWN);
    }

}

void Monster::move (int dir_p)
{
    if ((state == STANDING) || (state == MOVING) || (state == RUNNING))
    {
        dir = dir_p;
        if (state != RUNNING)
         animation->reset();
        state = RUNNING;
        animation->loop(true);
        animation->once = false;
        animation->play();
        if (dir_p == MONSTER_LEFT)
            animation->Move (-2, 0);
        else if (dir_p == MONSTER_RIGHT)
            animation->Move (2, 0);
        else if (dir_p == MONSTER_UP)
            animation->Move (0, -2);
        else if (dir_p == MONSTER_DOWN)
            animation->Move (0, 2);
    }
}

void Monster::hit (int deg)
{
  (void)deg;
  die ();
}

void Monster::state_manage ()
{
    if (!animation->isPlaying())
    {
        if (state == ATTACKING)
            state = STANDING;
    }
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
