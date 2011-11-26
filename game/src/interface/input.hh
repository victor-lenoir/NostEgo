#ifndef INPUT_HH_
# define INPUT_HH

# include <algorithm>
# include <SDL/SDL.h>
# include <SDL/SDL_ttf.h>
# include <SDL/SDL_image.h>
# include <SDL/SDL_rotozoom.h>
# include "../draw/animation.hh"
# include <iostream>

struct Input
{
  Input ();
  ~Input();
  void process_keyboard (SDLKey key);
  void process_mouse_click (int x, int y);
  void display (SDL_Surface* screen);
  void set_text (std::string str);

  bool cursor_loaded;
  Animation cursor;
  SDL_Surface* img;
  TTF_Font* font;
  std::string text;
  bool focus;
  SDL_Rect rect;
};
#endif
