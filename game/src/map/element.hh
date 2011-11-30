#ifndef ELEMENT_HH_
# define ELEMENT_HH_

# include <string>
# include <iostream>
# include <fstream>

# include <vector>
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>

# include "../draw/animation.hh"

class Element
{
public:
  Element (std::string element, int x, int y);
  ~Element ();

  void set_global (std::string hash);
  void process_keyboard_general (Uint8* key);
  virtual void process_keyboard (Uint8* key) {(void)key;}
  virtual void process_keyboard_bottom (Uint8* key) {(void)key;}
  virtual void process_keyboard_top (Uint8* key) {(void)key;}
  virtual void process_keyboard_left (Uint8* key) {(void)key;}
  virtual void process_keyboard_right (Uint8* key) {(void)key;}
  void display (SDL_Surface* screen,
		int offsetx,
		int offsety);
  Animation animation;
  bool global;
};
#endif
