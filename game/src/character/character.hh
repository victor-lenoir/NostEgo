#ifndef CHARACTER_HH_
# define CHARACTER_HH_

# include <string>
# include <map>
# include <vector>
# include <SFML/ImgAnim.hh>
# include <server/server.hh>

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
  Character();
  Character(std::string world_map_, int xmap_, int ymap_, int x_, int y_);

  ~Character ();
  void broadcast_maps();
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
  
  void load_characters(std::vector<Client*>* on_map_);
  std::vector<Client*>* on_map;
  std::string world_map;
  std::map<int, bool> keydowns;
  void share_position();
  bool is_key_down(int key);
  void keyboard_pressed(int key);
  void keyboard_released(int key);
  void process();
  std::string hash_map();
};

#endif
