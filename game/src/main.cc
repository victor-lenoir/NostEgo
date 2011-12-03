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
	// Close window : exit
	if (Event.Type == sf::Event::Closed)
	   g->app->Close();
     }
     if (clock.GetElapsedTime() * 1000 > (1000 / opt->fps))
     {
	g->app->Clear();
	opt->curr_fps = clock.GetElapsedTime();
	// Draw the sprite
	//g->app->Draw(Sprite);

	// Draw the string
	//g->app->Draw(Text);

	// Update the window
	g->app->Display();
	clock.Reset ();
     }
     /*
     else
	sleep;
     */
  }

  delete g;
  delete opt;

  return 0;
}
