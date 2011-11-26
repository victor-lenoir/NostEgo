#include "element.hh"

Element::~Element ()
{
  for (size_t i = 0; i < animations.size (); ++i)
    delete animations[i];
}

SDL_Surface* CreateSurface(Uint32 flags,int width,int height,const SDL_Surface* display)
{
  // 'display' is the surface whose format you want to match
  //  if this is really the display format, then use the surface returned from SDL_SetVideoMode

  const SDL_PixelFormat& fmt = *(display->format);
  return SDL_CreateRGBSurface(flags,width,height,
			      fmt.BitsPerPixel,
			      fmt.Rmask,fmt.Gmask,fmt.Bmask,fmt.Amask );
}

Element::Element (std::string element, int x, int y)
{
  std::string element_path = "media/maps/elements/";
  std::string img_path = "media/images/maps/elements/";
  int enable_animation;
  SDL_Rect rect;
  std::ifstream input;

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
  (void)x;
  (void)y;
  (void)rect;
  /*
  while (!input.eof ())
    {
      Animation* a = new Animation;
      input >> rect.x;
      input >> rect.y;
      input >> rect.w;
      input >> rect.h;

      SDL_Surface* dst = CreateSurface(tmp->flags, rect.w, rect.h, tmp);

      (void)x;
      (void)y;
      SDL_BlitSurface(tmp, &rect, dst, NULL);
      a->load (tmp, rect.x + x, rect.y + y, 1, 0);
      animations.push_back (a);
    }
  SDL_FreeSurface (tmp);
  */
}
