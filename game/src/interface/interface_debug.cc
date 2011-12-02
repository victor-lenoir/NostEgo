#include "interface_debug.hh"
#include "../game/game.hh"
#include <iostream>

void InterfaceDebug::display (SDL_Surface* screen)
{
   std::string todisplay = "";
   int y = 10;

   for (size_t i = 0; i < images.size(); ++i)
      delete images[i];
   images.clear ();
   todisplay = "X = " + int_to_string (g->player->animation.rect.x);
   y = add_hypertexte (opt->screen_w / 2, y, debug_font, todisplay.c_str (), 0, this, true)->h + y;

   todisplay = "Y = " + int_to_string (g->player->animation.rect.y);
   y = add_hypertexte (opt->screen_w / 2, y, debug_font, todisplay.c_str (), 0, this, true)->h + y;

   todisplay = "XMAP = " + int_to_string (g->xmap);
   y = add_hypertexte (opt->screen_w / 2, y, debug_font, todisplay.c_str (), 0, this, true)->h + y;

   todisplay = "YMAP = " + int_to_string (g->ymap);
   y = add_hypertexte (opt->screen_w / 2, y, debug_font, todisplay.c_str (), 0, this, true)->h + y;

   todisplay = "XOFF = " + int_to_string (g->xoff);
   y = add_hypertexte (opt->screen_w / 2, y, debug_font, todisplay.c_str (), 0, this, true)->h + y;

   todisplay = "YOFF = " + int_to_string (g->yoff);
   y = add_hypertexte (opt->screen_w / 2, y, debug_font, todisplay.c_str (), 0, this, true)->h + y;

   todisplay = "FPS = " + int_to_string (opt->curr_fps);
   y = add_hypertexte (opt->screen_w / 2, y, debug_font, todisplay.c_str (), 0, this, true)->h + y;

   BaseInterface<InterfaceDebug>::display (screen);
}

InterfaceDebug::InterfaceDebug()
{
   debug_font = TTF_OpenFont("media/fonts/stonehenge.ttf", 55);
   if (!debug_font)
      std::cout << "TTF OpenFont = " << TTF_GetError() << std::endl;
   add_hypertexte (opt->screen_w / 2, 10, debug_font, "0", 0, this, true);
}

InterfaceDebug::~InterfaceDebug ()
{
   TTF_CloseFont (debug_font);
}
