#ifndef INTERFACE_START_HH_
# define INTERFACE_START_HH_

# include "base_interface.hh"

class InterfaceStart : public BaseInterface
{
public:
   InterfaceStart ();
   ~InterfaceStart ();
   virtual void display (SDL_Surface* screen);
   void process_mouse (int x, int y);
private:
   TTF_Font* start_font;
};
#endif
