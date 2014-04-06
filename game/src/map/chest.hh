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
  Chest (int x, int y, std::ifstream& input, int id_);
  virtual void process_keyboard_bottom (Character* p);  
  bool open;
  void open_chest();
  virtual void update(sf::Packet& packet);
  
  std::string object;
};

#endif
