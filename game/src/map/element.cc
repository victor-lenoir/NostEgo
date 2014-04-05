#include "element.hh"
#include "../game/game.hh"

Element::~Element ()
{
}

void Element::process_keyboard_general ()
{
  /*
    process_keyboard ();
    if ((g->player->xp - g->player->xoff + g->player->width >= animation->GetPosition().x) &&
    (g->player->xp - g->player->xoff <= animation->GetPosition().x + animation->GetSubRect().GetWidth()) &&
    (g->player->yp - g->player->yoff - g->player->get_speed () + g->player->height / 2 >= animation->GetPosition().y) &&
    (g->player->yp - g->player->yoff - g->player->get_speed () + g->player->height / 2 <= animation->GetPosition().y + animation->GetSubRect().GetHeight()))
    {
    g->player->canup = false;
    process_keyboard_bottom ();
    }
    if ((g->player->xp - g->player->xoff + g->player->width >= animation->GetPosition().x) &&
    (g->player->xp - g->player->xoff <= animation->GetPosition().x + animation->GetSubRect().GetWidth()) &&
    (g->player->yp - g->player->yoff + g->player->get_speed () + g->player->height  >= animation->GetPosition().y) &&
    (g->player->yp - g->player->yoff + g->player->get_speed () + g->player->height <= animation->GetPosition().y + animation->GetSubRect().GetHeight()))
    {
    g->player->candown = false;
    process_keyboard_top ();
    }

    if ((g->player->xp - g->player->xoff + g->player->get_speed () + g->player->width >= animation->GetPosition().x) &&
    (g->player->xp - g->player->xoff + g->player->get_speed () <= animation->GetPosition().x + animation->GetSubRect().GetWidth()) &&
    (g->player->yp - g->player->yoff + g->player->height / 1.5 >= animation->GetPosition().y) &&
    (g->player->yp - g->player->yoff + g->player->height / 1.5 <= animation->GetPosition().y + animation->GetSubRect().GetHeight()))
    {
    g->player->canright = false;
    process_keyboard_left ();
    }

    if ((g->player->xp - g->player->xoff - g->player->get_speed () + g->player->width >= animation->GetPosition().x) &&
    (g->player->xp - g->player->xoff - g->player->get_speed () <= animation->GetPosition().x + animation->GetSubRect().GetWidth()) &&
    (g->player->yp - g->player->yoff + g->player->height / 1.5 >= animation->GetPosition().y) &&
    (g->player->yp - g->player->yoff + g->player->height / 1.5 <= animation->GetPosition().y + animation->GetSubRect().GetHeight()))
    {
    g->player->canleft = false;
    process_keyboard_right ();
    }
  */
}

void Element::load_animation() {
  if (!animation) {
    sf::Image* img;

    if (!img_mng->get (img_path.c_str (), img))
    {
      img->LoadFromFile(img_path.c_str ());
      img->SetSmooth(true);
    }
    animation = new ImgAnim (delay, img, nimage, nanim);
    if (stop_animation)
      animation->stop();
  }
}

int Element::width() {
  load_animation();
  return animation->GetSubRect().GetWidth();
}

int Element::height() {
  load_animation();
  return animation->GetSubRect().GetHeight();
}

void Element::display ()
{
  load_animation();
  animation->SetX (x);
  animation->SetY (y);
  app->Draw (*animation);
}


Element::Element ()
{

}

Element::Element (std::string element, int x_, int y_, int nanim_)
{
  std::string element_path = "media/maps/elements/";
  img_path = "media/images/maps/elements/";
  int enable_animation;
  std::ifstream input;
  x=x_;
  y=y_;
  stop_animation=false;
  nimage = 1;
  delay = 1.0;
  nanim=nanim_;
  global = false;
  element_path += element;
  input.open (element_path.c_str());
  if (!input.good())
  {
    std::cerr << "Element load error: " << element_path << std::endl;
    return;
  }
  input >> element_path;
  img_path += element_path;
  input >> enable_animation;
  if (enable_animation)
  {
    input >> nimage;
    input >> delay;
  }
  animation = 0;
}
