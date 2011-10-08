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
     {
       if (images[i].over && images[i].img_over)
	 SDL_BlitSurface (images[i].img_over, NULL, screen, &images[i].rect);
       else
	 SDL_BlitSurface (images[i].img, NULL, screen, &images[i].rect);
     }
}

void BaseInterface::process_mouse (int x, int y)
{
   for (size_t i = 0; i < images.size(); ++i)
   {
      if (images[i].handler)
      {
	 if ((x >= images[i].rect.x) &&
	     (x <= images[i].rect.x + images[i].rect.w)
	     && (y >= images[i].rect.y) &&
	     (y <= images[i].rect.y + images[i].rect.h))
	 {
	    images[i].over = true;
	 }
	 else
	    images[i].over = false;
      }
   }
}

void BaseInterface::process_mouse_click (int x, int y)
{
   for (size_t i = 0; i < images.size(); ++i)
   {
      if (images[i].handler)
      {
         if ((x >= images[i].rect.x) && (x <= images[i].rect.x + images[i].rect.w)
             && (y >= images[i].rect.y) && (y <= images[i].rect.y + images[i].rect.h))
         {
	   images[i].handler ();
         }
      }
   }
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
