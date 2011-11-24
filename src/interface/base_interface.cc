#include "base_interface.hh"

BaseInterface::~BaseInterface ()
{
  for (size_t i = 0; i < images.size(); ++i)
    {
      if (images[i].img_over)
	SDL_FreeSurface (images[i].img_over);
      if (images[i].img)
	SDL_FreeSurface (images[i].img);
    }
}

void BaseInterface::display (SDL_Surface* screen)
{
   for (size_t i = 0; i < images.size(); ++i)
     images[i].display (screen);
   for (size_t i = 0; i < inputs.size(); ++i)
     inputs[i].display (screen);
}

void BaseInterface::process_keyboard (SDLKey key)
{
  for (size_t i = 0; i < inputs.size(); ++i)
    inputs[i].process_keyboard (key);
}
void BaseInterface::process_mouse (int x, int y)
{
   for (size_t i = 0; i < images.size(); ++i)
     images[i].process_mouse (x, y);
}

void BaseInterface::process_mouse_click (int x, int y)
{
   for (size_t i = 0; i < images.size(); ++i)
     images[i].process_mouse_click (x, y);
   for (size_t i = 0; i < inputs.size(); ++i)
     inputs[i].process_mouse_click (x, y);
}

SDL_Rect* BaseInterface::add_input (int x,
				    int y,
				    int w,
				    int h,
				    TTF_Font* font)
{
  Input e;

  e.rect.x = x;
  e.rect.y = y;
  e.rect.w = w;
  e.rect.h = h;
  e.font = font;

  inputs.push_back (e);
  return &inputs.back ().rect;
}

SDL_Rect* BaseInterface::add_image (const char* img,
				    int x,
				    int y,
				    bool h_center)
{
  Image ne;

  SDL_Surface* tmp = IMG_Load (img);

  if (tmp)
    {
      ne.img = tmp;
      ne.rect.x = x;
      if (h_center)
	ne.rect.x -= ne.img->w / 2;
      ne.rect.y = y;
      ne.rect.w = ne.img->w;
      ne.rect.h = ne.img->h;
      images.push_back (ne);

      return &images.back().rect;
    }
  else
    {
      std::cerr << "Failed to load " << img << std::endl;
      return 0;
    }
}

SDL_Rect* BaseInterface::add_hypertexte (int x,
					 int y,
					 TTF_Font* font,
					 const char* text,
					 t_func handler,
					 bool h_center)
{
   Image ne;
   SDL_Color white = {255, 255, 255, 0};
   SDL_Color red = {255, 0, 0, 0};

   ne.img = TTF_RenderText_Blended(font, text, white);
   ne.img_over = TTF_RenderText_Blended(font, text, red);
   ne.rect.x = x;
   if (h_center)
     ne.rect.x -= ne.img->w / 2;
   ne.rect.y = y;
   ne.rect.w = ne.img->w;
   ne.rect.h = ne.img->h;
   ne.handler = handler;

   images.push_back (ne);
   return &images.back().rect;
}
