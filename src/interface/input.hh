#ifndef INPUT_HH_
# define INPUT_HH

# include <algorithm>

struct Input
{
  Input ()
  {
    focus = false;
    text = "";
    img = 0;
    font = 0;
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
     int w = rect.w;
     int h = rect.h;
     rect.y += h;
     rect.h = 1;

    SDL_FillRect (screen, &rect, SDL_MapRGB(screen->format, 255, 255, 255));

    rect.h = h;
    rect.y -= h;
    if (img)
      {
	 w = rect.w;
	 h = rect.h;
	 SDL_BlitSurface (img, NULL, screen, &rect);
	 rect.w = w;
	 rect.h = h;
      }
  }

  void set_text (std::string str)
  {
    SDL_Color white = {255, 255, 255, 0};
    int n = 0;

    text = str;

    n = text.size ();
    if (img)
    {
       SDL_FreeSurface (img);
       img = 0;
    }
    while (n > 0)
    {
       if (img)
       {
	  SDL_FreeSurface (img);
	  img = 0;
       }
       img = TTF_RenderText_Blended(font, text.substr(text.size() - n, n).c_str(), white);
       if (img->w < rect.w)
	  break;
       --n;
    }
  }

  SDL_Surface* img;
  TTF_Font* font;
  std::string text;
  SDL_Rect rect;
  bool focus;
};
#endif
