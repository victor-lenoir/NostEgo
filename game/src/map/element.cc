#include "element.hh"
#include "../game/game.hh"

Element::~Element ()
{
}

void Element::process_keyboard_general (Uint8* key)
{
   process_keyboard (key);

   if ((g->player->animation.rect.x - g->xoff + g->player->animation.rect.w >= animation.rect.x) &&
       (g->player->animation.rect.x - g->xoff <= animation.rect.x + animation.rect.w) &&
       (g->player->animation.rect.y - g->yoff + g->player->animation.rect.h / 2 >= animation.rect.y) &&
       (g->player->animation.rect.y - g->yoff + g->player->animation.rect.h / 2 <= animation.rect.y + animation.rect.h))
   {
      g->player->canup = false;
      process_keyboard_bottom (key);
   }
   if ((g->player->animation.rect.x - g->xoff + g->player->animation.rect.w >= animation.rect.x) &&
       (g->player->animation.rect.x - g->xoff <= animation.rect.x + animation.rect.w) &&
       (g->player->animation.rect.y - g->yoff + g->player->animation.rect.h / 2 >= animation.rect.y) &&
       (g->player->animation.rect.y - g->yoff + g->player->animation.rect.h / 2 <= animation.rect.y + animation.rect.h))
   {
      g->player->candown = false;
      process_keyboard_top (key);
    }

  if ((g->player->animation.rect.x - g->xoff + g->player->animation.rect.w >= animation.rect.x) &&
      (g->player->animation.rect.x - g->xoff <= animation.rect.x + animation.rect.w) &&
      (g->player->animation.rect.y - g->yoff + g->player->animation.rect.h / 2 >= animation.rect.y) &&
      (g->player->animation.rect.y - g->yoff + g->player->animation.rect.h / 2 <= animation.rect.y + animation.rect.h))
    {
      g->player->canright = false;
      process_keyboard_left (key);
    }
}

void Element::display (SDL_Surface* screen,
		       int offsetx,
		       int offsety)
{
  int backupx = animation.rect.x;
  int backupy = animation.rect.y;

  animation.rect.x += offsetx;
  animation.rect.y += offsety;
  animation.display (screen);
  animation.rect.x = backupx;
  animation.rect.y = backupy;
}

void Element::set_global (std::string hash)
{
  global = true;
  g->global_elements.insert (std::pair<std::string, Element*>(hash, this));
}

Element::Element (std::string element, int x, int y)
{
  std::string element_path = "media/maps/elements/";
  std::string img_path = "media/images/maps/elements/";
  int enable_animation;
  std::ifstream input;
  int nimage = 1;
  int delay = 0;

  global = false;
  element_path += element;
  input.open (element_path.c_str());
  if (!input.good())
    {
      std::cerr << "Element load error: " << element_path << std::endl;
      return;
    }
  input >> element_path;
  img_path += element_path;
  SDL_Surface* tmp = IMG_Load (img_path.c_str ());
  if (!tmp)
    {
      std::cerr << "Element image load error: " << img_path << std::endl;
      return;
    }
  input >> enable_animation;
  if (enable_animation)
    {
      input >> nimage;
      input >> delay;
    }
  animation.load (tmp, x, y, nimage, delay);
}
