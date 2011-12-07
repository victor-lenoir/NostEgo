#include "game/game.hh"
#include "option/option.hh"
#include <SFML/Graphics.hpp>
#include <iostream>

Game* g;
Option* opt;
sf::RenderWindow* app;

int main ()
{
  sf::Clock clock;
  sf::VideoMode vm = sf::VideoMode::GetDesktopMode();
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
	opt->curr_fps = 1000 / (clock.GetElapsedTime() * 1000);
	g->process ();
	g->display ();
	app->Display();
	clock.Reset ();
     }
     //else
     //sf::Sleep((1000 / opt->fps) - clock.GetElapsedTime() * 1000);
  }

  delete g;
  delete opt;

  return 0;
}
