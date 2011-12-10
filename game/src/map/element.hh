#ifndef ELEMENT_HH_
# define ELEMENT_HH_

# include <string>
# include <iostream>
# include <fstream>

# include <vector>

# include <SFML/ImgAnim.hh>

class Element
{
public:
  Element (std::string element, int x, int y, int nanim);
  ~Element ();

  void set_global (std::string hash);
  void process_keyboard_general ();
  virtual void process_keyboard () {}
  virtual void process_keyboard_bottom () {}
  virtual void process_keyboard_top () {}
  virtual void process_keyboard_left () {}
  virtual void process_keyboard_right () {}
  void display (int offsetx,
		int offsety);
  ImgAnim* animation;
  bool global;
};
#endif
