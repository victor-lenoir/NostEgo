#include "../option/option.hh"

template <typename T>
void BaseInterface<T>::display ()
{
   for (size_t i = 0; i < texts.size(); ++i)
      app->Draw (*texts[i].first);
}

template <typename T>
sf::FloatRect BaseInterface<T>::add_hypertexte (int x,
						int y,
						sf::Font* font,
						const char* text,
						InterfaceHandler handler)
{
   sf::String* tmp = new sf::String(text, *font, 50);

   tmp->SetX (x);
   tmp->SetY (y);
   texts.push_back (std::pair<sf::String*,InterfaceHandler>(tmp, handler));
   return tmp->GetRect();
}
