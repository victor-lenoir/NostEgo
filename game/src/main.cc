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
  app = new sf::RenderWindow(vm, "Nost ego");
  opt = new Option;
  g = new Game;
  g->init_game ();

  clock.Reset ();

  while (app->IsOpened())
  {
     sf::Event Event;
     while (app->GetEvent(Event))
     {
	if (Event.Type == sf::Event::Closed)
	   app->Close();
     }

     if (clock.GetElapsedTime() * 1000 > (1000 / opt->fps))
     {
	app->Clear();
	opt->curr_fps = clock.GetElapsedTime();
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
