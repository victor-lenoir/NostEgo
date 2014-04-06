#include "element.hh"
#include "../game/game.hh"

Element::~Element ()
{
}

void Element::process_keyboard_general(Character* p)
{
  process_keyboard ();
  if ((p->x + p->width >= x) &&
      (p->x <= x + width()) &&
      (p->y  - p->get_speed () + p->height / 2 >= y) &&
      (p->y  - p->get_speed () + p->height / 2 <= y + height()))
  {
    p->canup = false;
    process_keyboard_bottom ();
  }
  if ((p->x + p->width >= x) &&
      (p->x <= x + width()) &&
      (p->y  + p->get_speed () + p->height  >= y) &&
      (p->y  + p->get_speed () + p->height <= y + height()))
  {
    p->candown = false;
    process_keyboard_top ();
  }

  if ((p->x + p->get_speed () + p->width >= x) &&
      (p->x + p->get_speed () <= x + width()) &&
      (p->y  + p->height / 1.5 >= y) &&
      (p->y  + p->height / 1.5 <= y + height()))
  {
    p->canright = false;
    process_keyboard_left ();
  }

  if ((p->x - p->get_speed () + p->width >= x) &&
      (p->x - p->get_speed () <= x + width()) &&
      (p->y  + p->height / 1.5 >= y) &&
      (p->y  + p->height / 1.5 <= y + height()))
  {
    p->canleft = false;
    process_keyboard_right ();
  }
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
