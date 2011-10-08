#include "interface.hh"

#define WIDTH 1368

Interface::Interface ()
{
  TTF_Init ();
  for (int i = 0; i < MAX_IM; ++i)
    images[i] = 0;
  for (int i = 0; i < MAX_IM; ++i)
    rects[i] = 0;
  start_font = TTF_OpenFont("media/fonts/stonehenge.ttf", 55);
  if (!start_font)
    std::cout << "TTF OpenFont = " << TTF_GetError() << std::endl;
  set_state (START);
}

Interface::~Interface ()
{
  TTF_CloseFont(start_font);
  TTF_Quit ();
  free_images ();
}

void Interface::process ()
{

}

void Interface::set_state (int p_state)
{
  if (p_state == state)
    return;

  free_images ();
  state = p_state;
  if (p_state == START)
    {
      SDL_Color black = {255, 255, 255, 0};

      images[0] = IMG_Load ("media/images/interface/start.png");
      rects[0] = new SDL_Rect;
      rects[0]->x = WIDTH / 2 -  images[0]->w / 2;
      rects[0]->y = 100;

      images[1] = TTF_RenderText_Blended(start_font, "Create a new player",
					 black);
      rects[1] = new SDL_Rect;
      rects[1]->x = WIDTH / 2 - images[1]->w / 2;
      rects[1]->y = 300;
      rects[1]->w = images[1]->w;
      rects[1]->h = images[1]->h;

      images[2] = TTF_RenderText_Blended(start_font, "Load game",
                                         black);
      rects[2] = new SDL_Rect;
      rects[2]->x = rects[1]->x;
      rects[2]->y = rects[1]->y + rects[1]->h;
      rects[2]->w = images[2]->w;
      rects[2]->h = images[2]->h;

      images[3] = TTF_RenderText_Blended(start_font, "Exit",
                                         black);
      rects[3] = new SDL_Rect;
      rects[3]->x = rects[1]->x;
      rects[3]->y = rects[2]->y + rects[2]->h;
      rects[3]->w = images[3]->w;
      rects[3]->h = images[3]->h;

    }
}

void Interface::free_images ()
{
  for (int i = 0; i < MAX_IM; ++i)
    {
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
    }
}

void Interface::display_start (SDL_Surface* screen)
{
  for (int i = 0; i < MAX_IM; ++i)
    if (images[i])
      SDL_BlitSurface (images[i], NULL, screen, rects[i]);
}

void Interface::display (SDL_Surface* screen)
{
  if (state == START)
    display_start (screen);
}
