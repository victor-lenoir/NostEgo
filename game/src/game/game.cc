#include <iostream>
#include <sstream>

#include "game.hh"
#include "../option/option.hh"

std::string int_to_string (int n)
{
  std::ostringstream oss;
  oss << n;
  return oss.str();
}

void Game::init_game ()
{
  if (!init)
  {
    interface = new Interface;
    init = true;
  }
}

Game::Game ()
{
  std::string ip = "127.0.0.1";
  int port = 2012;

  sf::IPAddress ServerAddress = ip;
  if (Socket.Connect(port, ServerAddress) != sf::Socket::Done)
  {
    std::cerr << "Could not connect to server " << ip << " on port " << port << std::endl;
    exit (32);
  }
  init = false;
  interface = 0;
  map  = new Map;
  state = START;
  done = false;
}

Game::~Game ()
{
  init = false;
  if (interface)
    delete interface;
  if (map)
    delete map;
  for (std::map<int, Character*>::iterator it = characters.begin();
       it != characters.end (); ++it)
  {
    delete (it->second);
  }

  Socket.Close();
}

void Game::load_map()
{
  std::string tmp = "media/maps/" + characters.begin()->second->world_map;

  map->load_map ((tmp + int_to_string (characters.begin()->second->xmap) + "-" +
                  int_to_string (characters.begin()->second->ymap)).c_str ());
}

int Game::get_state ()
{
  return state;
}

void Game::set_state (int state_p)
{
  state = state_p;
  interface->clean ();
}

void Game::process ()
{
  sf::Event Event;


  while (app->GetEvent(Event))
  {
    switch (Event.Type)
    {
    case sf::Event::Closed:
      app->Close();
      break;
    case sf::Event::MouseMoved:
      interface->process_mouse_move (Event.MouseMove.X, Event.MouseMove.Y);
      break;
    case sf::Event::MouseButtonPressed:
      interface->process_mouse_click (Event.MouseButton.X, Event.MouseButton.Y);
      break;
    case sf::Event::KeyPressed:
      if (Event.Key.Code == sf::Key::Escape)
        app->Close();
      else if (state == MAP)
      {
        sf::Packet Packet;

        Packet << NETWORK_KEYBOARD_PRESSED
               << (int)Event.Key.Code;
        Socket.Send(Packet);
      }
      break;
    case sf::Event::KeyReleased:
      if (state == MAP)
      {
        sf::Packet Packet;

        Packet << NETWORK_KEYBOARD_RELEASED
               << Event.Key.Code;
        Socket.Send(Packet);
      }
      break;
    default:
      break;
    }
  }
}

void Game::display ()
{
  if (g->get_state() == MAP)
  {
    map->display_background();
    map->display();
  }
  interface->display ();
}
