#include "../option/option.hh"

template <typename T>
void BaseInterface<T>::display ()
{
   for (size_t i = 0; i < texts.size(); ++i)
      app->Draw (*texts[i].first);
}
