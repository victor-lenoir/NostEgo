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

   virtual void display ();

   sf::FloatRect add_hypertexte (int x,
				 int y,
				 sf::Font* font,
				 const char* text,
				 InterfaceHandler handler);

   std::vector<std::pair<sf::String*,InterfaceHandler> > texts;
   //std::vector<Animation*> animations;
   //std::vector<Image<T>*> images;
   //std::vector<Input*>	 inputs;
};

#include "base_interface.hxx"

#endif
