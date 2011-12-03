#ifndef INTERFACE_START_HH_
# define INTERFACE_START_HH_

# include "base_interface.hh"

class InterfaceStart : public BaseInterface<InterfaceStart>
{
public:
   InterfaceStart ();
   ~InterfaceStart ();
  void quit ();
  void create_new_player ();
};
#endif
