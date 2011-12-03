#ifndef BASE_INTERFACE_HH_
# define BASE_INTERFACE_HH_

# include <vector>
# include <string>
# include <iostream>
# include "../option/option.hh"
# include <SFML/Graphics.hpp>

template <class T>
class BaseInterface
{
public:
   typedef void (T::*InterfaceHandler)();
  ~BaseInterface ()
  {
     /*
    for (size_t i = 0; i < images.size(); ++i)
      delete images[i];
    for (size_t i = 0; i < inputs.size(); ++i)
      delete inputs[i];
    for (size_t i = 0; i < animations.size(); ++i)
      delete animations[i];
     */
  }

  void display ();

  virtual void clean ()
  {
     /*
    for (size_t i = 0; i < images.size(); ++i)
      images[i]->over = false;
    for (size_t i = 0; i < inputs.size(); ++i)
      {
	if (inputs[i]->img)
	  {
	    SDL_FreeSurface (inputs[i]->img);
	    inputs[i]->img = 0;
	  }
	inputs[i]->focus = false;
	inputs[i]->text = "";
      }
     */
  }

   sf::FloatRect add_hypertexte (int x,
				 int y,
				 sf::Font* font,
				 const char* text,
				 InterfaceHandler handler,
				 T* owner_handler,
				 bool h_center)
   {
      sf::String* tmp = new sf::String(text, *font, 50);

      tmp->SetX (x);
      tmp->SetY (y);
      texts.push_back (std::pair<sf::String*,InterfaceHandler>(tmp, handler));
      return tmp->GetRect();
   }

   std::vector<std::pair<sf::String*,InterfaceHandler> > texts;
  //std::vector<Animation*> animations;
  //std::vector<Image<T>*> images;
  //std::vector<Input*>	 inputs;
};

#include "base_interface.hxx"

#endif
