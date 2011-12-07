#ifndef CHEST_HH_
# define CHEST_HH_

# include "element.hh"
# include <string>
# include <iostream>

# include <fstream>

class Chest : public Element
{
public:
  Chest (int x, int y, std::ifstream& input, std::string hash);
  virtual void process_keyboard_bottom ();
};

#endif
