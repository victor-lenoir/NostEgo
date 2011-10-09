#include "input.hh"

Input::Input ()
{
  cursor_loaded = false;
  focus = false;
  text = "";
  img = 0;
  font = 0;
}

Input::~Input()
{
  if (img)
    SDL_FreeSurface (img);
}

void Input::process_keyboard (SDLKey key)
{
  if (!focus)
    return;

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


void Input::process_mouse_click (int x, int y)
{
  if ((x >= rect.x) && (x <= rect.x + rect.w) &&
      (y >= rect.y) && (y <= rect.y + rect.h))
    focus = true;
  else
    focus = false;
}

void Input:: display (SDL_Surface* screen)
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

  if (!cursor_loaded)
    {
      SDL_Surface* tmp = IMG_Load ("media/images/interface/input.png");
      cursor.load (zoomSurface (tmp, 1.0, rect.h - 10, 0), 0, 0, 2, 1000);
      SDL_FreeSurface (tmp);
      cursor_loaded = true;
    }
  if (focus)
    {
      cursor.rect.y = rect.y + 5;
      cursor.rect.x = rect.x;
      if (img)
	cursor.rect.x += img->w + 2;
      cursor.display (screen);
    }
}

void Input::set_text (std::string str)
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
      img = TTF_RenderText_Blended(font,
				   text.substr(text.size() - n, n).c_str(),
				   white);
      if (img->w < rect.w)
	break;
      --n;
    }
}

