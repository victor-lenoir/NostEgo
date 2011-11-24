#include "base_interface.hh"

BaseInterface::~BaseInterface ()
{
   for (size_t i = 0; i < images.size(); ++i)
   {
      if (images_over[i] != 0)
	 SDL_FreeSurface (images_over[i]);
      if (images[i] != 0)
	 SDL_FreeSurface (images[i]);
      if (rects[i] != 0)
	 delete rects[i];
   }
}

void BaseInterface::display (SDL_Surface* screen)
{
   for (size_t i = 0; i < rects.size(); ++i)
      if (images[i])
      {
	 if (over[i])
	    SDL_BlitSurface (images_over[i], NULL, screen, rects[i]);
	 else
	    SDL_BlitSurface (images[i], NULL, screen, rects[i]);
      }
}

void BaseInterface::process_mouse (int x, int y)
{
   for (size_t i = 0; i < rects.size(); ++i)
   {
      if (handlers[i])
      {
	 if ((x >= rects[i]->x) && (x <= rects[i]->x + rects[i]->w)
	     && (y >= rects[i]->y) && (y <= rects[i]->y + rects[i]->h))
	 {
	    over[i] = true;
	 }
	 else
	    over[i] = false;
      }
   }
}

void BaseInterface::process_mouse_click (int x, int y)
{
   for (size_t i = 0; i < rects.size(); ++i)
   {
      if (rects[i])
      {
         if ((x >= rects[i]->x) && (x <= rects[i]->x + rects[i]->w)
             && (y >= rects[i]->y) && (y <= rects[i]->y + rects[i]->h))
         {
	    if (handlers[i])
	    {
	       handlers[i] ();
	       // CALL HANDLER
	    }
         }
      }
   }
}

void BaseInterface::add_image (const char* img,
			       int x,
			       int y,
			       bool h_center)
{
   images.push_back (IMG_Load (img));
   rects.push_back (new SDL_Rect);
   rects.back ()->x = x;
   if (h_center)
      rects.back ()->x  -= images.back()->w / 2;
   rects.back ()->y = y;
   images_over.push_back (0);
   handlers.push_back (0);
   over.push_back (false);
}

SDL_Rect* BaseInterface::add_hypertexte (int x,
					 int y,
					 TTF_Font* font,
					 const char* text,
					 t_func handler,
					 bool h_center)
{
   SDL_Color white = {255, 255, 255, 0};
   SDL_Color red = {255, 0, 0, 0};

   images.push_back (TTF_RenderText_Blended(font, text, white));
   images_over.push_back (TTF_RenderText_Blended(font, text, red));
   rects.push_back (new SDL_Rect);
   rects.back ()->x = x;
   if (h_center)
      rects.back ()->x -= images.back()-> w / 2;
   rects.back ()->y = y;
   rects.back ()->w = images.back()->w;
   rects.back ()->h = images.back()->h;
   over.push_back (false);
   handlers.push_back (handler);

   return rects.back();
}
