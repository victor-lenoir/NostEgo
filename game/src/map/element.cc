#include "element.hh"
#include "../game/game.hh"

Element::~Element ()
{
  delete animation;
  animation = 0;
}

void Element::process_keyboard_general ()
{
  process_keyboard ();
  if ((g->player->animation->GetPosition().x - g->xoff + g->player->animation->GetSubRect().GetWidth() >= animation->GetPosition().x) &&
      (g->player->animation->GetPosition().x - g->xoff <= animation->GetPosition().x + animation->GetSubRect().GetWidth()) &&
      (g->player->animation->GetPosition().y - g->yoff - g->player->get_speed () + g->player->animation->GetSubRect().GetHeight() / 2 >= animation->GetPosition().y) &&
      (g->player->animation->GetPosition().y - g->yoff - g->player->get_speed () + g->player->animation->GetSubRect().GetHeight() / 2 <= animation->GetPosition().y + animation->GetSubRect().GetHeight()))
    {
      g->player->canup = false;
      process_keyboard_bottom ();
    }
  if ((g->player->animation->GetPosition().x - g->xoff + g->player->animation->GetSubRect().GetWidth() >= animation->GetPosition().x) &&
      (g->player->animation->GetPosition().x - g->xoff <= animation->GetPosition().x + animation->GetSubRect().GetWidth()) &&
      (g->player->animation->GetPosition().y - g->yoff + g->player->get_speed () + g->player->animation->GetSubRect().GetHeight()  >= animation->GetPosition().y) &&
      (g->player->animation->GetPosition().y - g->yoff + g->player->get_speed () + g->player->animation->GetSubRect().GetHeight() <= animation->GetPosition().y + animation->GetSubRect().GetHeight()))
    {
      g->player->candown = false;
      process_keyboard_top ();
    }

  if ((g->player->animation->GetPosition().x - g->xoff + g->player->get_speed () + g->player->animation->GetSubRect().GetWidth() >= animation->GetPosition().x) &&
      (g->player->animation->GetPosition().x - g->xoff + g->player->get_speed () <= animation->GetPosition().x + animation->GetSubRect().GetWidth()) &&
      (g->player->animation->GetPosition().y - g->yoff + g->player->animation->GetSubRect().GetHeight() / 1.5 >= animation->GetPosition().y) &&
      (g->player->animation->GetPosition().y - g->yoff + g->player->animation->GetSubRect().GetHeight() / 1.5 <= animation->GetPosition().y + animation->GetSubRect().GetHeight()))
    {
      g->player->canright = false;
      process_keyboard_left ();
    }

  if ((g->player->animation->GetPosition().x - g->xoff - g->player->get_speed () + g->player->animation->GetSubRect().GetWidth() >= animation->GetPosition().x) &&
      (g->player->animation->GetPosition().x - g->xoff - g->player->get_speed () <= animation->GetPosition().x + animation->GetSubRect().GetWidth()) &&
      (g->player->animation->GetPosition().y - g->yoff + g->player->animation->GetSubRect().GetHeight() / 1.5 >= animation->GetPosition().y) &&
      (g->player->animation->GetPosition().y - g->yoff + g->player->animation->GetSubRect().GetHeight() / 1.5 <= animation->GetPosition().y + animation->GetSubRect().GetHeight()))
    {
      g->player->canleft = false;
      process_keyboard_right ();
    }
}

void Element::display (int offsetx,
                       int offsety)
{
  animation->Move(offsetx, offsety);
  app->Draw (*animation);
  animation->Move(-offsetx, -offsety);
}

void Element::set_global (std::string hash)
{
  global = true;
  g->global_elements.insert (std::pair<std::string, Element*>(hash, this));
}

Element::Element (std::string element, int x, int y)
{
  std::string element_path = "media/maps/elements/";
  std::string img_path = "media/images/maps/elements/";
  int enable_animation;
  std::ifstream input;
  int nimage = 1;
  float delay = 1.0;
  sf::Image* img = new sf::Image;

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
   img->LoadFromFile(img_path.c_str ());
   img->SetSmooth(true);
   animation = new ImgAnim (delay, img, nimage, 1);
   animation->SetX (x);
   animation->SetY (y);
}
