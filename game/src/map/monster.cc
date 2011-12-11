#include "monster.hh"
#include "../option/option.hh"
#include <iostream>

enum
{
  LEFT,
  DOWN,
  UP,
  RIGHT
};

Monster::Monster (int x, int y, std::ifstream& input, std::string hash, std::string element)
  : Element (element, x, y, 8)
{
  animation->pause ();
  dir = LEFT;
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
    state = DYING;
    refresh_dir ();
    animation->loop(false);
    animation->once = true;
    animation->reset();
    animation->play();
    dead = true;
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
    move (LEFT);
}

void Monster::move (int dir_p)
{
    if ((state == STANDING) || (state == MOVING) || (state == RUNNING))
    {
        dir = dir_p;
        if (state != MOVING)
         animation->reset();
        state = MOVING;
        animation->loop(true);
        animation->once = false;
        animation->play();
        if (dir_p == LEFT)
            animation->Move (-1, 0);
        else if (dir_p == RIGHT)
            animation->Move (1, 0);
        else if (dir_p == UP)
            animation->Move (0, -1);
        else if (dir_p == DOWN)
            animation->Move (0, 1);
    }
}

void Monster::hit (int deg)
{
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
    attack (DOWN);
}

void Monster::process_keyboard_top ()
{
    if (app->GetInput().IsKeyDown (sf::Key::Space))
        hit (12);
    attack (UP);
}

void Monster::process_keyboard_left ()
{
    if (app->GetInput().IsKeyDown (sf::Key::Space))
        hit (12);
    attack (LEFT);
}

void Monster::process_keyboard_right ()
{
    if (app->GetInput().IsKeyDown (sf::Key::Space))
        hit (12);
    attack (RIGHT);
}

void Monster::process_keyboard ()
{
    state_manage();
    AI ();
    refresh_dir ();
}
