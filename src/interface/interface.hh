#ifndef INTERFACE_HH_
# define INTERFACE_HH_

# include <SDL/SDL.h>
# include <SDL/SDL_image.h>
# include <SDL/SDL_ttf.h>
# include <iostream>
# include <string>
# include <vector>

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
  void generate_menu (int y_,
		      int offset,
		      TTF_Font* font,
		      std::vector<std::pair <std::string, void*> >& slots);
  void free_images ();
  void process_menu ();
   void process_mouse (int x, int y);

private:
  SDL_Surface*	images[MAX_IM];
  SDL_Surface*  images_over[MAX_IM];
  SDL_Rect*	rects[MAX_IM];
  void*		handlers[MAX_IM];
   bool		over[MAX_IM];
  TTF_Font* start_font;
  int state;
};

#endif
