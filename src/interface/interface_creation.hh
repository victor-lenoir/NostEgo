#ifndef INTERFACE_CREATION_HH_
# define INTERFACE_CREATION_HH_

# include "base_interface.hh"

class InterfaceCreation : public BaseInterface
{
public:
   InterfaceCreation ();
   ~InterfaceCreation ();

private:
  TTF_Font* creation_font;
  TTF_Font* input_font;
};
#endif
