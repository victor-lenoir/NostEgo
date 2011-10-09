#ifndef BASE_INTERFACE_HH_
# define BASE_INTERFACE_HH_

# include <SDL/SDL_image.h>
# include <SDL/SDL_ttf.h>
# include <SDL/SDL.h>
# include <vector>
# include <string>
# include <iostream>
# include "image.hh"
# include "input.hh"
# include "animation.hh"

extern int g_w;
extern int g_h;

template <class T> class Image;

template <class T> class BaseInterface
{
public:
  typedef void (T::*InterfaceHandler)();
public:

  ~BaseInterface ()
  {
    for (size_t i = 0; i < images.size(); ++i)
      delete images[i];
    for (size_t i = 0; i < inputs.size(); ++i)
      delete inputs[i];
    for (size_t i = 0; i < animations.size(); ++i)
      delete animations[i];
  }

  virtual void display (SDL_Surface* screen)
  {
    for (size_t i = 0; i < images.size(); ++i)
      images[i]->display (screen);
    for (size_t i = 0; i < inputs.size(); ++i)
      inputs[i]->display (screen);
    for (size_t i = 0; i < animations.size(); ++i)
      animations[i]->display (screen);
  }

  virtual void process_mouse (int x, int y)
  {
    for (size_t i = 0; i < images.size(); ++i)
      images[i]->process_mouse (x, y);
  }

  virtual void process_mouse_click (int x, int y)
  {
    for (size_t i = 0; i < images.size(); ++i)
      images[i]->process_mouse_click (x, y);
    for (size_t i = 0; i < inputs.size(); ++i)
      inputs[i]->process_mouse_click (x, y);
  }

  virtual void process_keyboard (SDLKey key)
  {
    for (size_t i = 0; i < inputs.size(); ++i)
      inputs[i]->process_keyboard (key);
  }
  virtual void clean ()
  {
    for (size_t i = 0; i < images.size(); ++i)
      images[i]->over = false;
    for (size_t i = 0; i < inputs.size(); ++i)
      {
	if (inputs[i]->img)
	  {
	    SDL_FreeSurface (inputs[i]->img);
	    inputs[i]->img = 0;
	  }
	inputs[i]->focus = false;
	inputs[i]->text = "";
      }

  }
  SDL_Rect* add_image (const char* img, int x, int y, bool h_center)
  {
    Image<T>* ne = new Image<T>;

    SDL_Surface* tmp = IMG_Load (img);

    if (tmp)
      {
	ne->img = tmp;
	ne->rect.x = x;
	if (h_center)
	  ne->rect.x -= ne->img->w / 2;
	ne->rect.y = y;
	ne->rect.w = ne->img->w;
	ne->rect.h = ne->img->h;
	images.push_back (ne);

	return &images.back()->rect;
      }
    else
      {
	std::cerr << "Failed to load " << img << std::endl;
	return 0;
      }
  }

  SDL_Rect* add_hypertexte (int x,
			    int y,
			    TTF_Font* font,
			    const char* text,
			    InterfaceHandler handler,
			    T* owner_handler,
			    bool h_center)
  {
    Image<T>* ne = new Image<T>;
    SDL_Color white = {255, 255, 255, 0};
    SDL_Color red = {255, 0, 0, 0};

    ne->img = TTF_RenderText_Blended(font, text, white);
    ne->img_over = TTF_RenderText_Blended(font, text, red);
    ne->rect.x = x;
    if (h_center)
      ne->rect.x -= ne->img->w / 2;
    ne->rect.y = y;
    ne->rect.w = ne->img->w;
    ne->rect.h = ne->img->h;
    ne->handler = handler;
    ne->owner_handler = owner_handler;
    images.push_back (ne);
    return &images.back()->rect;
  }

  SDL_Rect* add_input (int x, int y, int w, int h, TTF_Font* font)
  {
    Input* e = new Input;

    e->rect.x = x;
    e->rect.y = y;
    e->rect.w = w;
    e->rect.h = h;
    e->font = font;

    inputs.push_back (e);
    return &inputs.back ()->rect;
  }

  SDL_Rect* add_animation (SDL_Surface* p_img,
			   int x,
			   int y,
			   int p_max_step,
			   int p_delay_process)
  {
    Animation* a = new Animation;

    a->load (p_img, x, y, p_max_step, p_delay_process);
    animations.push_back (a);
    return &animations.back ()->rect;
  }

  std::vector<Animation*> animations;
  std::vector<Image<T>*> images;
  std::vector<Input*>	 inputs;
};
#endif
