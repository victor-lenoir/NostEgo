#ifndef INTERFACE_DEBUG_HH_
# define INTERFACE_DEBUG_HH_

# include "base_interface.hh"

class InterfaceDebug : public BaseInterface<InterfaceDebug>
{
public:
   InterfaceDebug ();
   ~InterfaceDebug ();
  virtual void display ();
private:
  sf::Font* stone;
};
#endif
