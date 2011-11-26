#include "element.hh"

Element::~Element ()
{
}

Element::Element (std::string element, int x, int y)
{
  std::string element_path = "media/maps/elements/";
  std::string img_path = "media/images/maps/elements/";
  int enable_animation;
  std::ifstream input;

  element_path += element;
  input.open (element_path.c_str());
  if (!input.good())
    {
      std::cerr << "Element load error: " << element_path << std::endl;
      return;
    }
  input >> element_path;
  img_path += element_path;
  SDL_Surface* tmp = IMG_Load (img_path.c_str ());
  if (!tmp)
    {
      std::cerr << "Element image load error: " << img_path << std::endl;
      return;
    }
  input >> enable_animation;
  animation.load (tmp, x, y, 1, 0);
}
