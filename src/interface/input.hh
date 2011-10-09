#ifndef INPUT_HH_
# define INPUT_HH_

# include <SDL/SDL_draw.h>

struct Input
{
  Input ()
  {
    focus = false;
    text = "";
    img = 0;
  }

  ~Input()
  {
    if (img)
      SDL_FreeSurface (img);
  }

  void process_keyboard (SDLKey key)
  {
    if (key == SDLK_RETURN)
      focus = false;

    if ((key == 8) && (text.size () > 0))
      {
	text.erase (text.size() - 1, 1);
	set_text (text);
      }
    if (((key >= 97) && (key <= 97 + 26)) || (key == 32))
      {
	if ((text == "") && (key != 32))
	  text += (char)(key - 32);
	else
	  text += (char)key;
	set_text (text);
      }
  }

  void process_mouse_click (int x,
			    int y)
  {
    if ((x >= rect.x) && (x <= rect.x + rect.w) &&
	(y >= rect.y) && (y <= rect.y + rect.h))
	focus = true;
    else
      focus = false;
  }

  void display (SDL_Surface* screen)
  {
    if (focus)
      Draw_FillRound(screen, rect.x - 2, rect.y - 2, rect.w + 4,
		     rect.h + 4, 6, SDL_MapRGB(screen->format, 200, 0, 0));
    Draw_FillRound(screen, rect.x, rect.y, rect.w,
		   rect.h, 6, SDL_MapRGB(screen->format, 175, 175, 175));
    if (img)
      {
	int w = rect.w;
	int h = rect.h;
	SDL_BlitSurface (img, NULL, screen, &rect);
	rect.w = w;
	rect.h = h;
      }
  }

  void set_text (std::string str)
  {
    SDL_Color black = {0, 0, 0, 0};

    text = str;
    if (img)
      SDL_FreeSurface (img);
    img = TTF_RenderText_Blended(font, text.c_str(), black);
  }

  SDL_Surface* img;
  TTF_Font* font;
  std::string text;
  SDL_Rect rect;
  bool focus;
};
#endif
