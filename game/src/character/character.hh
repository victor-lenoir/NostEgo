#ifndef CHARACTER_HH_
# define CHARACTER_HH_

# include "../draw/animation.hh"
# include <string>
# include <SDL/SDL_image.h>
# include <SDL/SDL.h>

class Character
{
public:
  void move (float x, float y, int dir_p);
  void process_keyboard (Uint8 *keystate);
  void display (SDL_Surface* screen);
  Animation animation;
  int dir;
  std::string name;
  void stand ();
  void load (const char* img, int nimage);
private:
  Uint32 last;
  Uint32 curr;
};

#endif
