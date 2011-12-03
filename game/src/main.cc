#include "game/game.hh"
#include "option/option.hh"
#include <SFML/Graphics.hpp>
#include <iostream>

Game* g;
Option* opt;

int main ()
{
  sf::Clock clock;
  opt = new Option;
  g = new Game;
  g->init_game ();

  clock.Reset ();
  while (g->app->IsOpened())
  {
     sf::Event Event;
     while (g->app->GetEvent(Event))
     {
	if (Event.Type == sf::Event::Closed)
	   g->app->Close();
     }

     if (clock.GetElapsedTime() * 1000 > (1000 / opt->fps))
     {
	g->app->Clear();
	opt->curr_fps = clock.GetElapsedTime();
	g->process ();
	g->display ();
	g->app->Display();
	clock.Reset ();
     }
     //else
     //sf::Sleep((1000 / opt->fps) - clock.GetElapsedTime() * 1000);
  }

  delete g;
  delete opt;

  return 0;
}
