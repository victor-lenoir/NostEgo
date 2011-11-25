#ifndef INTERFACE_DEBUG_HH_
# define INTERFACE_DEBUG_HH_

# include "base_interface.hh"

class InterfaceDebug : public BaseInterface<InterfaceDebug>
{
public:
   InterfaceDebug ();
   ~InterfaceDebug ();
   void display (SDL_Surface* screen);
private:
   TTF_Font* debug_font;
};
#endif
