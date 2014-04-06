#ifndef ELEMENT_HH_
# define ELEMENT_HH_

# include <string>
# include <iostream>
# include <fstream>

# include <vector>

# include <SFML/ImgAnim.hh>
# include <SFML/Network.hpp>
# include <network/network.hh>

class Character;
class Element
{
public:
  Element (std::string element, int x, int y, int nanim, int id_);
  ~Element ();
  virtual void affect (sf::Packet& packet) {(void)packet;}
  virtual void sendPacket (sf::SocketTCP& client) {(void)client;}
  void process_keyboard_general (Character* p);
  virtual void process_keyboard (Character* p) {(void)p;}
  virtual void process_keyboard_bottom (Character* p) {(void)p;}
  virtual void process_keyboard_top (Character* p) {(void)p;}
  virtual void process_keyboard_left (Character* p) {(void)p;}
  virtual void process_keyboard_right (Character* p) {(void)p;}
  virtual void process_keyboard_other (Character* p) {(void)p;}
  void display ();
  void load_animation();
  int width();
  int height();
  ImgAnim* animation;
  int x;
  int y;
  int id;
  bool modified;
  int stop_animation;
  std::string img_path;
  bool global;
  std::string hash_;
  int nanim;
  float delay;
  int nimage;
};
#endif
