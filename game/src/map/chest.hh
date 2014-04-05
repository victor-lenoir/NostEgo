#ifndef CHEST_HH_
# define CHEST_HH_

# include "element.hh"
# include <string>
# include <iostream>

# include <fstream>
# include <network/network.hh>

class Chest : public Element
{
public:
  Chest (int x, int y, std::ifstream& input);
  bool open;
  std::string object;
};

#endif
