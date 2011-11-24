#include "interface_start.hh"
#include <iostream>

InterfaceStart::InterfaceStart()
{
   int y = 0;

   start_font = TTF_OpenFont("media/fonts/stonehenge.ttf", 55);
   if (!start_font)
      std::cout << "TTF OpenFont = " << TTF_GetError() << std::endl;


   add_image ("media/images/interface/start.png", g_w / 2, 100, true);

   y = add_hypertexte (g_w / 2, 350, start_font, "Create new player", 0, true)->h + 350;
   y = add_hypertexte (g_w / 2, y, start_font, "Load game", 0, true)->h + y;
   y = add_hypertexte (g_w / 2, y, start_font, "Exit", 0, true)->h + y;
}

InterfaceStart::~InterfaceStart ()
{
   TTF_CloseFont (start_font);
}

void InterfaceStart::display (SDL_Surface* screen)
{
   for (size_t i = 0; i < rects.size(); ++i)
   {
      if (images[i])
      {
	 if (over[i])
	    SDL_BlitSurface (images_over[i], NULL, screen, rects[i]);
	 else
	    SDL_BlitSurface (images[i], NULL, screen, rects[i]);
      }
   }
}
void InterfaceStart::process_mouse (int      x,
				    int      y)
{
   for (size_t i = 0; i < rects.size(); ++i)
   {
      if (rects[i])
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
