#ifndef ELEMENT_HH_
# define ELEMENT_HH_

# include <string>
# include <iostream>
# include <fstream>

# include <vector>

# include <SFML/ImgAnim.hh>
# include <SFML/Network.hpp>
# include <network/network.hh>

class Element
{
public:
  Element (std::string element, int x, int y, int nanim);
  Element ();
  ~Element ();
  virtual void affect (sf::Packet& packet) {(void)packet;}
  virtual void sendPacket (sf::SocketTCP& client) {std::cout << "WRONG CALL" << std::endl; (void)client;}
  void set_global (std::string hash);
  void set_global_silent (std::string hash);
  void process_keyboard_general ();
  virtual void process_keyboard () {}
  virtual void process_keyboard_bottom () {}
  virtual void process_keyboard_top () {}
  virtual void process_keyboard_left () {}
  virtual void process_keyboard_right () {}
  virtual void process_keyboard_other () {}
  virtual void process_keyboard_other_bottom () {}
  virtual void process_keyboard_other_top () {}
  virtual void process_keyboard_other_left () {}
  virtual void process_keyboard_other_right () {}
  void display (int offsetx,
		int offsety);
  ImgAnim* animation;
  bool global;
    std::string hash_;
};
#endif
