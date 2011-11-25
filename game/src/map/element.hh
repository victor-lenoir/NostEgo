#ifndef ELEMENT_HH_
# define ELEMENT_HH_

# include <string>
# include <iostream>
# include <fstream>
# include "../draw/animation.hh"

# include <vector>
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>

class Element
{
public:
  Element (std::string element, int x, int y);
  ~Element ();

   void process_keyboard_general (Uint8* key)
   {
      process_keyboard (key);
      // if player bottom the element then
      process_keyboard_bottom (key);
   }

  virtual void process_keyboard (Uint8* key) {(void)key;}
  virtual void process_keyboard_bottom (Uint8* key) {(void)key;}
  void display (SDL_Surface* screen,
		int offsetx,
		int offsety);
  Animation animation;
};
#endif
