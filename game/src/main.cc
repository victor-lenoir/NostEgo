#include "game/game.hh"
#include "option/option.hh"
#include <SFML/Graphics.hpp>
#include <iostream>

Game* g;
Option* opt;
sf::RenderWindow* app;
MemoryManager<sf::Image>* img_mng;

int main ()
{
  sf::Clock clock;
  sf::VideoMode vm = sf::VideoMode::GetDesktopMode();

  img_mng = new MemoryManager<sf::Image>;
  app = new sf::RenderWindow(vm, "Nost ego", sf::Style::Fullscreen);
  opt = new Option;
  g = new Game;
  g->init_game ();

  clock.Reset ();

  while (app->IsOpened())
  {
    if (clock.GetElapsedTime() * 1000 > (1000 / opt->fps))
    {
      app->Clear();
      opt->curr_fps = 1.f / clock.GetElapsedTime();
      clock.Reset ();
      g->process ();
      g->display ();
      app->Display();
    }
    else
     sf::Sleep((1.0/ (float)opt->fps) - clock.GetElapsedTime());
  }

  delete g;
  delete opt;
  delete img_mng;

  return 0;
}
