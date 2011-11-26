#include "character.hh"
#include <iostream>

void Character::display (SDL_Surface* screen)
{
  animation.display (screen);
}

void Character::move_up ()
{
  dir = 3;
  animation.rect.y -= 4;
  moved ();
}

void Character::move_down ()
{
  dir = 0;
  animation.rect.y += 4;
  moved ();
}

void Character::move_left ()
{
  dir = 1;
  animation.rect.x -= 4;
  moved ();
}

void Character::moved ()
{
  animation.stepping = true;
  animation.mask.y = dir * (animation.img->h / 8);
}
void Character::move_right ()
{
  dir = 2;
  animation.rect.x += 4;
  moved ();
}

void Character::process_keyboard (SDLKey key)
{
  if (key == SDLK_UP)
    move_up ();
  else if (key == SDLK_DOWN)
    move_down ();
  else if (key == SDLK_RIGHT)
    move_right ();
  else if (key == SDLK_LEFT)
    move_left ();
}

void Character::load (const char* img, int nimage)
{
  std::string e = "media/images/characters/";
  dir = 0;

  e += img;
  animation.load (IMG_Load (e.c_str ()), 100, 100,
		  nimage, 50);
  animation.mask.h /= 8;
  animation.playing = false;
  animation.mask.y = dir * (animation.img->h / 8);
}
