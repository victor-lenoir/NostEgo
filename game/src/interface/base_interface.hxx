#include "../option/option.hh"

template <typename T>
BaseInterface<T>::~BaseInterface ()
{
  for (size_t i = 0; i < texts.size(); ++i)
    delete texts[i].first;
  for (size_t i = 0; i < animations.size(); ++i)
    {

      delete animations[i].first;
    }
}

template <typename T>
void BaseInterface<T>::display ()
{
  for (size_t i = 0; i < texts.size(); ++i)
    app->Draw (*texts[i].first);
  for (size_t i = 0; i < animations.size(); ++i)
    app->Draw (*animations[i].first);
}

template <typename T>
void BaseInterface<T>::process_mouse_move (int x, int y)
{
  for (size_t i = 0; i < texts.size(); ++i)
    {
      if ((texts[i].second.second) &&
	  (texts[i].first->GetRect ().Contains (x, y)))
	texts[i].first->SetColor (sf::Color::Red);
      else
	texts[i].first->SetColor (sf::Color::White);
    }
}

template <typename T>
void BaseInterface<T>::process_mouse_click (int x, int y)
{
  for (size_t i = 0; i < texts.size(); ++i)
    {
      if ((texts[i].second.second) &&
	  (texts[i].first->GetRect ().Contains (x, y)))
	(texts[i].second.first->*(texts[i].second.second)) ();
    }
  for (size_t i = 0; i < animations.size(); ++i)
    {
      if ((animations[i].second.second) &&
          (animations[i].first->GetSubRect ().Contains (x, y)))
        (animations[i].second.first->*(animations[i].second.second)) ();
    }
}

template <typename T>
sf::FloatRect BaseInterface<T>::add_hypertexte (int x,
						int y,
						sf::Font* font,
						const char* text,
						T* owner,
						InterfaceHandler handler,
						bool center)
{
   sf::String* tmp = new sf::String(text, *font, 50);

   if (center)
     tmp->SetX (x - tmp->GetRect().GetWidth () / 2);
   else
     tmp->SetX (x);
   tmp->SetY (y);
   texts.push_back (std::pair<sf::String*, std::pair <T*, InterfaceHandler> >(tmp, std::pair <T*, InterfaceHandler> (owner, handler)));
   return tmp->GetRect();
}

template <typename T>
sf::IntRect BaseInterface<T>::add_animation (int x,
					     int y,
					     float delay_p,
					     int nanimation,
					     int nframe,
					     const char* img_path,
					     T* owner,
					     InterfaceHandler handler,
					     bool center)
{
  sf::Image* img;

  if (!img_mng->get (img_path, img))
    img->LoadFromFile (img_path);
  ImgAnim* tmp = new ImgAnim (delay_p, img, nframe, nanimation);
  if (center)
    tmp->SetX (x - tmp->GetSubRect().GetWidth () / 2);
  else
    tmp->SetX (x);
  tmp->SetY (y);
  animations.push_back (std::pair<ImgAnim*, std::pair <T*, InterfaceHandler> >(tmp, std::pair <T*, InterfaceHandler> (owner, handler)));
  return tmp->GetSubRect ();
}
