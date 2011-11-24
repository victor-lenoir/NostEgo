#ifndef INTERFACE_START_HH_
# define INTERFACE_START_HH_

# include "base_interface.hh"

class InterfaceStart : public BaseInterface
{
public:
   InterfaceStart ();
   ~InterfaceStart ();

private:
   TTF_Font* start_font;
};
#endif
