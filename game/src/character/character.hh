#ifndef CHARACTER_HH_
# define CHARACTER_HH_

# include <string>
# include <map>
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
  int get_speed ();
  bool canup;
  bool candown;
  bool canright;
  bool canleft;
  int id;
  int x;
  int y;
  int xmap;
  int ymap;
  int width;
  int height;

  std::string world_map;
  std::map<sf::Key::Code, bool> keydowns;
  bool is_key_down(sf::Key::Code key);
  void keyboard_pressed(sf::Key::Code key);
  void keyboard_released(sf::Key::Code key);
  void process();
  void share_position();
};

#endif
