#ifndef CHEST_HH_
# define CHEST_HH_

# include "element.hh"
# include <string>
# include <iostream>
# include <SDL/SDL.h>

class Chest : public Element
{
public:
  Chest (int x, int y, std::string object);
  virtual void process_keyboard_bottom (Uint8* key);
};

#endif
