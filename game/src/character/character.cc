#include "character.hh"
#include "../game/game.hh"
#include <iostream>

void Character::share_position ()
{
  sf::Packet Packet;
  /*std::cout << "CLIENT MOVING ID = " << id << std::endl;
    std::cout << "SEND X = " << animation->GetPosition().x - xoff
    << "; Y = " << animation->GetPosition().y - yoff << std::endl;
  */
  Packet << NETWORK_CHARACTER_MOVE
         << (int)id
         << xmap
         << ymap
         << (int)x
         << (int)y
         << (int)dir;
  g->Socket.Send(Packet);
}

void Character::keyboard_pressed(sf::Key::Code key) {
  keydowns[key] = true;
}

void Character::keyboard_released(sf::Key::Code key) {
  keydowns[key] = false;
}

void Character::process() {
  process_keyboard();
}

void Character::display ()
{
  if (!animation) {
    sf::Image* img;
    if (!img_mng->get ("media/images/characters/healer.png", img))
    {
      img->LoadFromFile("media/images/characters/healer.png");
      img->SetSmooth(true);
    }
    animation = new ImgAnim (0.05, img, 8, 8);
    animation->pause ();

  }
  animation->SetX (x);
  animation->SetY (y);
  app->Draw(*animation);
}

int Character::get_speed ()
{
  return (400 / (1 + opt->curr_fps));
}

void Character::move (float xpar,
                      float ypar,
                      int dir_p)
{
  float deltax = get_speed ();
  float deltay = get_speed ();

  deltax *= xpar;
  deltay *= ypar;

  dir = dir_p;
}

bool Character::is_key_down(sf::Key::Code key) {
  return keydowns[key];
}
void Character::process_keyboard ()
{
  bool up = is_key_down(sf::Key::Up);
  bool down = is_key_down(sf::Key::Down);
  bool left = is_key_down(sf::Key::Left);
  bool right = is_key_down(sf::Key::Right);

  if (up && canup && right && canright)
    move (SQRT2, -SQRT2, UP_RIGHT);
  else if (down && candown && right && canright)
    move (SQRT2, SQRT2, DOWN_RIGHT);
  else if (up && canup && left && canleft)
    move (-SQRT2, -SQRT2, UP_LEFT);
  else if (down && candown && left && canleft)
    move (-SQRT2, SQRT2, DOWN_LEFT);
  else if (up && canup)
    move (0, -1, UP);
  else if (down && candown)
    move (0, 1, DOWN);
  else if (right && canright)
    move (1, 0, RIGHT);
  else if (left && canleft)
    move (-1, 0, LEFT);
  else
  {
    if (up && right)
      dir = UP_RIGHT;
    else if (down && right)
      dir = DOWN_RIGHT;
    else if (up && left)
      dir = UP_LEFT;
    else if (down && left)
      dir = DOWN_LEFT;
    else if (up)
      dir = UP;
    else if (down)
      dir = DOWN;
    else if (right)
      dir = RIGHT;
    else if (left)
      dir = LEFT;
  }
  canright = true;
  canleft = true;
  candown = true;
  canup = true;
  if (up || down || left || right)
    share_position();
}

Character::Character ()
{
  id = -1;
  dir = DOWN;
  x = WIDTH_MAP / 2;
  y = HEIGHT_MAP / 2;
  world_map = "test";
  xmap = 0;
  ymap = 0;
  width = 32;
  height = 64;
  animation = 0;
}

Character::~Character ()
{
  if (animation) {
    delete animation;
  }
}
