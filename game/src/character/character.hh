#ifndef CHARACTER_HH_
# define CHARACTER_HH_

# include <string>
# include <SFML/ImgAnim.hh>

# define SQRT2 sqrt(2) / 2.0

enum
  {
    DOWN,
    LEFT,
    RIGHT,
    UP,
    DOWN_LEFT,
    DOWN_RIGHT,
    UP_LEFT,
    UP_RIGHT
  };

class Character
{
public:
  Character ();
  ~Character ();
  void move (float x, float y, int dir_p);
  void process_keyboard ();
  void display ();
  ImgAnim* animation;
  int dir;
  std::string name;
  void stand ();
  int get_speed ();
  bool canup;
  bool candown;
  bool canright;
  bool canleft;
private:
  void move_player (int deltax, int deltay);
  void refresh_map ();
};

#endif
