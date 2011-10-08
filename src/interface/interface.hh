#ifndef INTERFACE_HH_
# define INTERFACE_HH_

# include <SDL/SDL.h>
# include <SDL/SDL_image.h>
# include <SDL/SDL_ttf.h>
# include <iostream>

# define MAX_IM	5

enum
{
  START,
  CREATION,
  MAP,
  FIGHT
};

class Interface
{
public:
  Interface ();
  ~Interface ();
  void process ();
  void display (SDL_Surface* screen);
  void display_start (SDL_Surface* screen);
  void set_state (int p_state);
  void free_images ();
private:
  SDL_Surface* images[MAX_IM];
  SDL_Rect* rects[MAX_IM];
  TTF_Font* start_font;
  int state;
};

#endif
