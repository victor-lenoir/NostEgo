#ifndef GAME_HH_
# define GAME_HH_

# include <SDL/SDL.h>

# define WIDTH 1366
# define HEIGHT 768

struct Game
{
  Game ();
  ~Game ();
  void process ();
  void display ();

  void process_exit ();
  bool done;
  SDL_Surface* screen;
};

#endif
