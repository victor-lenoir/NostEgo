#ifndef MONSTER_HH_
# define MONSTER_HH_

# include "element.hh"
# include <string>
# include <iostream>

# include <fstream>

enum
{
  STANDING,
  MOVING,
  RUNNING,
  ATTACKING,
  DYING
};

class Monster : public Element
{
public:
  virtual void process_keyboard ();
  void attack (int dir_p);
  void die ();
  void AI ();
  void state_manage ();
  void move (int dir_p);
  void hit (int deg);
  virtual void process_keyboard_bottom ();
  virtual void process_keyboard_top ();
  virtual void process_keyboard_left ();
  virtual void process_keyboard_right ();
  void refresh_dir ();
  Monster (int x, int y, std::ifstream& input, std::string element, int id_);
  int dir;
  int state;
  bool dead;
};

#endif
