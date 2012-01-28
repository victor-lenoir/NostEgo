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
  virtual void affect (sf::Packet& packet);
  virtual void sendPacket (sf::SocketTCP& client);
  Chest (int x, int y, std::ifstream& input, std::string hash);
  Chest (int x, int y, std::string hash, std::string object);
  virtual void process_keyboard_bottom ();
  virtual void process_keyboard_other_bottom ();
  bool open;
};

#endif
