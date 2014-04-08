#include "game/game.hh"
#include "option/option.hh"
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <map/chest.hh>

Game* g;
Option* opt;
sf::RenderWindow* app;
MemoryManager<sf::Image>* img_mng;

void listen_server (void* data);
void listen_server (void* data)
{
  int n;
  int id;
  int x;
  int y;
  int xmap;
  int ymap;
  int dir;
  std::string str;
  std::string world_map;
  (void)data;
  sf::Packet Packet;
  int code;
  Chest* ch;
  int code2;

  g->Socket.SetBlocking(false);
  while (g->Socket.Receive(Packet) == sf::Socket::Done)
  {
    Packet >> code;
    switch (code)
    {
    case NETWORK_CHEST:
      Packet >> str >> id >> n;
      ch = (Chest*)g->map->get_element_by_id(n);
      ch->open_chest();
      // Player id received object str from chest n
      break;
    case NETWORK_NEW_MAP:
      Packet >> world_map >> xmap >> ymap;
      Packet >> n;
      for (std::map<int, Character*>::iterator it = g->characters.begin(); it != g->characters.end(); it++) {
        delete it->second;
      }
      g->characters.clear();
      for (int k = 0; k < n; ++k) {
        Packet >> id >> x >> y >> dir;
        g->characters[id] = new Character(world_map, xmap, ymap, x, y, dir);
      }
      g->load_map();
      while (1) {
        Packet >> code2;
        if (code2 == NETWORK_EOF) break;
        switch (code2) {
        case NETWORK_CHEST_IS_OPEN:
          Packet >> id;
          ch = (Chest*)g->map->get_element_by_id(id);
          ch->open_chest();
          break;
        }
      }
      break;
    case NETWORK_CHARACTER_MOVE:
      Packet >> id >> x >> y >> dir;
      g->characters[id]->x = x;
      g->characters[id]->y = y;
      g->characters[id]->dir = dir;
      g->characters[id]->load_animation();
      g->characters[id]->animation->play();
      break;

      break;
    case NETWORK_EXIT_MAP:
      Packet >> n;
      g->characters.erase(n);
      break;
    default:
      std::cerr << "ERR CODE NOT HANDLE ("
                << code << ")"
                << std::endl;
      break;
    }
  }
}

int main ()
{
  sf::Clock clock;
  //sf::VideoMode vm = sf::VideoMode::GetDesktopMode();
  sf::VideoMode vm = sf::VideoMode(WIDTH_MAP, HEIGHT_MAP);
  sf::Packet sPacket;

  img_mng = new MemoryManager<sf::Image>;
  app = new sf::RenderWindow(vm, "Nost ego", sf::Style::Fullscreen);
  //app = new sf::RenderWindow(vm, "Nost ego");
  opt = new Option;
  g = new Game;
  g->init_game ();

  sPacket << NETWORK_NEW_CHARACTER;
  g->Socket.Send(sPacket);

  clock.Reset ();
  //tr.Launch ();
  while (app->IsOpened())
  {
    listen_server(0);
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
