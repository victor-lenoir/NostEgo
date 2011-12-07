#include "character.hh"
#include "../game/game.hh"
#include <iostream>

void Character::display ()
{
  app->Draw (*animation);
}

int Character::get_speed ()
{
  return 10;
  //return ((16 * 20) / (1 + opt->curr_fps));
}

void Character::refresh_map ()
{
  /*
  if (animation.rect.x - g->xoff > WIDTH_MAP)
    {
      g->xoff += WIDTH_MAP;
      ++g->xmap;
      g->load_maps ();
    }
  if (animation.rect.x - g->xoff < 0)
    {
      g->xoff -= WIDTH_MAP;
      --g->xmap;
      g->load_maps ();
    }
  if (animation.rect.y - g->yoff > HEIGHT_MAP)
    {
      g->yoff += HEIGHT_MAP;
      ++g->ymap;
      g->load_maps ();
    }
  if (animation.rect.y - g->yoff < 0)
    {
      g->yoff -= HEIGHT_MAP;
      --g->ymap;
      g->load_maps ();
    }
*/
}
void Character::move_player (int deltax,
			     int deltay)
{
  if ((int)deltax > 0)
    {
      if ((int)animation->GetPosition().x > 3 * opt->screen_w / 4)
        g->xoff -= (int)deltax;
      else
        animation->Move ((int)deltax, 0);
    }
  else
    {
      if ((int)animation->GetPosition().x < opt->screen_w / 4)
        g->xoff -= (int)deltax;
      else
	animation->Move ((int)deltax, 0);
    }

  if ((int)deltay > 0)
    {
      if ((int)animation->GetPosition().y > 3 * opt->screen_h / 4)
        g->yoff -= (int)deltay;
      else
        animation->Move (0, (int)deltay);
    }
  else
    {
      if ((int)animation->GetPosition().y < opt->screen_h / 4)
        g->yoff -= (int)deltax;
      else
        animation->Move (0, (int)deltay);
    }
}

void Character::move (float x,
		      float y,
		      int dir_p)
{
  float deltax = get_speed ();
  float deltay = get_speed ();

  deltax *= x;
  deltay *= y;

  dir = dir_p;

  animation->setAnimRow(dir);
  animation->play ();
  move_player (deltax, deltay);
  refresh_map ();
}

void Character::stand ()
{
  animation->setAnimRow(dir);
  animation->setFrame (0);
}


void Character::process_keyboard ()
{
  bool up = app->GetInput().IsKeyDown (sf::Key::Up);
  bool down =app->GetInput().IsKeyDown (sf::Key::Down);
  bool left =app->GetInput().IsKeyDown (sf::Key::Left);
  bool right =app->GetInput().IsKeyDown (sf::Key::Right);

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
      animation->stop ();
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
       stand ();
    }
  canright = true;
  canleft = true;
  candown = true;
  canup = true;
}


Character::Character ()
{
  sf::Image* img = new sf::Image;
  dir = DOWN;
  img->LoadFromFile("media/images/characters/healer.png");
  img->SetSmooth(true);
  animation = new ImgAnim (img, 8, 8);
  animation->SetX (WIDTH_MAP / 2);
  animation->SetY (HEIGHT_MAP / 2);
  animation->pause ();
}

Character::~Character ()
{
  delete animation;
}
