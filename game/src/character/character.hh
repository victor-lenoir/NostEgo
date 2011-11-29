#ifndef CHARACTER_HH_
# define CHARACTER_HH_

# include "../draw/animation.hh"
# include <string>
# include <SDL/SDL_image.h>
# include <SDL/SDL.h>

# define SQRT2 sqrt(2) / 2.0

enum
  {
    DOWN,
    LEFT,
    RIGHT,
    UP,
    DOWN_LEFT,
    DOWN_RIGHT,
    UP_LEFT,
    UP_RIGHT
  };

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
  void move_player (int deltax, int deltay);
  void refresh_map ();
  Uint32 last;
  Uint32 curr;
};

#endif
