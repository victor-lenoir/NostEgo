#ifndef BASE_INTERFACE_HH_
# define BASE_INTERFACE_HH_

# include <SDL/SDL_image.h>
# include <SDL/SDL_ttf.h>
# include <SDL/SDL.h>
# include <vector>
# include <string>
# include <iostream>
# include "image.hh"
# include "input.hh"

extern int g_w;
extern int g_h;

typedef void (*t_func)();

class BaseInterface
{
public:
   ~BaseInterface ();
   virtual void display (SDL_Surface* screen);
   virtual void process_mouse (int x, int y);
   virtual void process_mouse_click (int x, int y);
  virtual void process_keyboard (SDLKey key);
   SDL_Rect* add_image (const char* img, int x, int y, bool h_center);

   SDL_Rect* add_hypertexte (int x,
			     int y,
			     TTF_Font* font,
			     const char* text,
			     t_func handler,
			     bool h_center);

  SDL_Rect* add_input (int x, int y, int w, int h);

  std::vector<Image>	images;
  std::vector<Input>	inputs;
};
#endif
