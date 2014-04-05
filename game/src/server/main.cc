#include <iostream>
#include <SFML/Network.hpp>
#include <network/network.hh>
#include <vector>
#include <map/chest.hh>
#include <game/game.hh>
#include <server/server.hh>

sf::SelectorTCP Selector;
sf::SocketTCP Listener;
Game* g;
Option* opt;
sf::RenderWindow* app;
MemoryManager<sf::Image>* img_mng;


std::map<std::string, std::vector<Client*> > clients_per_map;
std::map<sf::SocketTCP, Client*> clients;

int currid = 0;

void handle (sf::Packet Packet, sf::SocketTCP client);
void handle (sf::Packet Packet, sf::SocketTCP client)
{
  int code;
  sf::Packet sPacket;
  int key;
  std::vector<Client*> on_map;
  Packet >> code;

  switch (code)
  {
  case NETWORK_NEW_CHARACTER:
    clients[client]->c->broadcast_maps();
    break;
  case NETWORK_KEYBOARD_PRESSED:
    Packet >> key;
    clients[client]->c->keyboard_pressed(key);
    break;
  case NETWORK_KEYBOARD_RELEASED:
    Packet >> key;
    clients[client]->c->keyboard_released(key);
    break;
  default:
    std::cerr << "Unknown code (" << code << ")" << std::endl;
    break;
  }
}
void processing_server(void* data);

void processing_server(void* data) {
  sf::Clock clock;
  (void)data;
  float fps = 40;
  while (1) {
    if (clock.GetElapsedTime() * 1000 > (1000 / fps))
    {
      for (std::map<sf::SocketTCP, Client*>::iterator it=clients.begin(); it != clients.end(); ++it) {
        it->second->c->process();
      }
      clock.Reset();
    }
    else
      sf::Sleep((1.0/ fps) - clock.GetElapsedTime());
  }
}

int main ()
{
  sf::Thread tr (processing_server);
  tr.Launch();
  if (!Listener.Listen(2012))
  {
    std::cerr << "Binding to port 2012 failed" << std::endl;
    return 1;
  }
  Selector.Add(Listener);
  std::cout << "Server launch..." << std::endl;
  while (true)
  {
    size_t i;
    unsigned int nsock = Selector.Wait();
    for (i = 0; i < nsock; ++i)
    {
      sf::SocketTCP Socket = Selector.GetSocketReady(i);;

      if (Socket == Listener)
      {
        sf::IPAddress Address;
        sf::SocketTCP client;
        Listener.Accept(client, &Address);
        std::cout << "Client connected ! (" << Address << ")" << std::endl;
        Selector.Add(client);
        Client* c1 = new Client;
        c1->socket = client;
        c1->c = new Character();
        c1->c->id = currid++;

        clients.insert(std::pair<sf::SocketTCP, Client*>(client, c1));
        if (clients_per_map.count(c1->c->hash_map()) == 0)
          clients_per_map.insert(std::pair<std::string, std::vector<Client*> >(c1->c->hash_map(), std::vector<Client*>()));
        clients_per_map[c1->c->hash_map()].push_back(c1);
        c1->c->load_characters(&clients_per_map[c1->c->hash_map()]);
      }
      else
      {
        sf::Packet Packet;
        if (Socket.Receive(Packet) == sf::Socket::Done)
        {
          handle (Packet, Socket);
        }
        else
        {
          std::cout << "Client exit" << std::endl;
          sf::Packet sPacketd;
          sPacketd << NETWORK_EXIT_MAP;
          sPacketd << clients[Socket]->c->id;
          std::vector<Client*>& oh = clients_per_map[clients[Socket]->c->hash_map()];

          for (std::vector<Client*>::iterator it = oh.begin() ; it != oh.end(); ++it) {
            if ((*it)->c->id == clients[Socket]->c->id) {
              oh.erase(it);
              clients[Socket]->c->broadcast_maps();
              delete (*it)->c;
              delete (*it);

              break;
            }
          }
          clients.erase(Socket);
          
          Selector.Remove(Socket);
        }
      }
    }
  }
  return 0;
}
