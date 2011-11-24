#include "interface.hh"
#include "../game/game.hh"

Interface::Interface ()
{
  TTF_Init ();
  for (int i = 0; i < MAX_IM; ++i)
  {
    over[i] = false;
    images[i] = 0;
    images_over[i] = 0;
    rects[i] = 0;
    handlers[i] = 0;
  }

  start_font = TTF_OpenFont("media/fonts/stonehenge.ttf", 55);
  if (!start_font)
    std::cout << "TTF OpenFont = " << TTF_GetError() << std::endl;
  state = -1;
  set_state (START);
}

Interface::~Interface ()
{
  TTF_CloseFont(start_font);
  TTF_Quit ();
  free_images ();
}

void Interface::process_mouse (int	x,
			       int	y)
{
   for (int i = 0; i < MAX_IM; ++i)
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

void Interface::generate_menu (int y_,
			       int offset,
			       TTF_Font* font,
			       std::vector<std::pair <std::string, void*> >& slots)
{
   (void)offset;
   (void)slots;
   (void)font;
   SDL_Color white = {255, 255, 255, 0};
   SDL_Color red = {255, 0, 0, 0};
   int y = y_;
   int maxw = 0;
   int imaxw = 0;

   for (size_t k = 0; k < slots.size(); ++k)
   {
      k += offset;
      images[k] = TTF_RenderText_Blended(font, slots[k - offset].first.c_str(),
					 white);
      images_over[k] = TTF_RenderText_Blended(font, slots[k - offset].first.c_str(),
					 red);
      if (maxw < images[k]->w)
      {
	 maxw = images[k]->w;
	 imaxw = k;
      }
      k -= offset;
   }

   for (size_t k = 0; k < slots.size(); ++k)
   {
      k += offset;
      rects[k] = new SDL_Rect;
      rects[k]->x = g_w / 2 - images[imaxw]->w / 2;
      rects[k]->y = y;
      rects[k]->w = images[k]->w;
      rects[k]->h = images[k]->h;
      y += images[k]->h;
      k -= offset;
   }
}

void Interface::set_state (int p_state)
{
  if (p_state == state)
    return;

  free_images ();
  state = p_state;
  if (p_state == START)
    {
      std::vector<std::pair <std::string, void*> > slots;

      slots.push_back (std::pair<std::string, void*> ("Create a new player", (void*)0));
      slots.push_back (std::pair<std::string, void*> ("Load game", (void*)0));
      slots.push_back (std::pair<std::string, void*> ("Exit", (void*)0));

      images[0] = IMG_Load ("media/images/interface/start.png");
      rects[0] = new SDL_Rect;
      rects[0]->x = g_w / 2 -  images[0]->w / 2;
      rects[0]->y = 100;
      generate_menu (rects[0]->y + images[0]->h + 150, 1, start_font, slots);
    }
}

void Interface::free_images ()
{
  for (int i = 0; i < MAX_IM; ++i)
    {
      over[i] = false;
      if (images_over[i] != 0)
      {
	 SDL_FreeSurface (images_over[i]);
	 images_over[i] = 0;
      }
      if (images[i] != 0)
	{
	  SDL_FreeSurface (images[i]);
	  images[i] = 0;
	}
      if (rects[i] != 0)
	{
	  delete rects[i];
	  rects[i] = 0;
	}
      handlers[i] = 0;
    }
}

void Interface::display_start (SDL_Surface* screen)
{
  for (int i = 0; i < MAX_IM; ++i)
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

void Interface::display (SDL_Surface* screen)
{
  if (state == START)
    display_start (screen);
}
