#ifndef BASE_INTERFACE_HH_
# define BASE_INTERFACE_HH_

# include <vector>
# include <string>
# include <iostream>
# include "../option/option.hh"
# include <SFML/Graphics.hpp>
# include <SFML/ImgAnim.hh>

template <class T>
class BaseInterface
{
public:
   typedef void (T::*InterfaceHandler)();

  ~BaseInterface ();
  virtual void display ();
  virtual void process_mouse_move (int x, int y);
  virtual void process_mouse_click (int x, int y);
  sf::IntRect add_animation (int x,
			       int y,
			       int nanimation,
			       int nframe,
			       const char* img_path,
			       T* owner,
			       InterfaceHandler handler,
			       bool center);

   sf::FloatRect add_hypertexte (int x,
				 int y,
				 sf::Font* font,
				 const char* text,
				 T* owner,
				 InterfaceHandler handler,
				 bool center);

  std::vector<std::pair<sf::String*, std::pair <T*, InterfaceHandler> > > texts;
  std::vector<std::pair<ImgAnim*, std::pair <T*, InterfaceHandler> > > animations;
};

#include "base_interface.hxx"

#endif
