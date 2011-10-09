#ifndef INPUT_HH_
# define INPUT_HH

# include <algorithm>
# include <SDL/SDL.h>
# include <SDL/SDL_ttf.h>
# include "animation.hh"

struct Input
{
  Input ();
  ~Input();
  void process_keyboard (SDLKey key);
  void process_mouse_click (int x, int y);
  void display (SDL_Surface* screen);
  void set_text (std::string str);

  Animation cursor;
  SDL_Surface* img;
  TTF_Font* font;
  std::string text;
  SDL_Rect rect;
  bool focus;
};
#endif
