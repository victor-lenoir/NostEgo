#ifndef MONSTER_HH_
# define MONSTER_HH_

# include "element.hh"
# include <string>
# include <iostream>

# include <fstream>

class Monster : public Element
{
public:
  virtual void process_keyboard ();
  void attack ();
  void die ();
  void refresh_dir ();
  Monster (int x, int y, std::ifstream& input, std::string hash, std::string element);
  int dir;
  bool dead;
};

#endif
