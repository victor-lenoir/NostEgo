#ifndef BASE_INTERFACE_HH_
# define BASE_INTERFACE_HH_
# include <SDL/SDL_image.h>
# include <SDL/SDL_ttf.h>
# include <SDL/SDL.h>
# include <vector>
# include <string>

extern int g_w;
extern int g_h;

class BaseInterface
{
public:
   ~BaseInterface ()
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

   virtual void display (SDL_Surface* screen) = 0;

   void add_image (const char* img,
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

     SDL_Rect* add_hypertexte (int x,
			      int y,
			      TTF_Font* font,
			      const char* text,
			       void* handler,
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

   std::vector<SDL_Surface*>  images;
   std::vector<SDL_Surface*>  images_over;
   std::vector<SDL_Rect*>     rects;
   std::vector<void*>         handlers;
   std::vector<bool>          over;
};
#endif
