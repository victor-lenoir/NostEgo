#ifndef IMAGE_HH_
# define IMAGE_HH_

template <class T> class BaseInterface;

template <class T> struct Image
{
  Image ()
  {
    img = 0;
    img_over = 0;
    handler = 0;
    over = false;
  }

  void process_mouse_click (int x,
			    int y)
  {
    if (handler && (x >= rect.x) && (x <= rect.x + rect.w)
	&& (y >= rect.y) && (y <= rect.y + rect.h))
      (owner_handler->*(handler)) ();
  }

  void process_mouse (int x,
		      int y)
  {
    if (handler)
      {
	if ((x >= rect.x) &&
	    (x <= rect.x + rect.w)
	    && (y >= rect.y) &&
	    (y <= rect.y + rect.h))
	  {
            over = true;
	  }
	else
	  over = false;
      }
  }

  void display (SDL_Surface* screen)
  {
    if (over && img_over)
      SDL_BlitSurface (img_over, NULL, screen, &rect);
    else if (img)
      SDL_BlitSurface (img, NULL, screen, &rect);
  }

  ~Image ()
  {
    if (img)
      SDL_FreeSurface (img);
    if (img_over)
      SDL_FreeSurface (img_over);
  }

  SDL_Rect rect;
  T* owner_handler;
  typename BaseInterface<T>::InterfaceHandler handler;
  bool over;
  SDL_Surface* img;
  SDL_Surface* img_over;
};
#endif
