#ifndef CHARACTER_HH_
# define CHARACTER_HH_

# include "../draw/animation.hh"
# include <string>
# include <SDL/SDL_image.h>
# include <SDL/SDL.h>

class Character
{
public:
  void moved ();
  void move_up ();
  void move_down ();
  void move_left ();
  void move_right ();
  void process_keyboard (SDLKey key);
  void display (SDL_Surface* screen);
  Animation animation;
  int dir;
  std::string name;
  void load (const char* img, int nimage);
};

#endif
