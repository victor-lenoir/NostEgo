#include <iostream>
#include <SFML/Network.hpp>
#include <network/network.hh>
#include <vector>
#include <map/chest.hh>
#include <game/game.hh>

Game* g;
Option* opt;
sf::RenderWindow* app;
MemoryManager<sf::Image>* img_mng;

sf::SelectorTCP Selector;
sf::SocketTCP Listener;
struct Client
{
    size_t id;
    sf::SocketTCP socket;
};
std::vector<Client> clients;
int currid = 0;
std::map<std::string, Element*> global_elements;

void broadcast (sf::Packet Packet, sf::SocketTCP* client)
{
    for (size_t i = 0; i < clients.size(); ++i)
    {
        if ((!client) || ((*client) != clients[i].socket))
             clients[i].socket.Send(Packet);
    }
}

void handle (sf::Packet Packet, sf::SocketTCP client)
{
    int code;
    std::string str;
    sf::Packet sPacket;
    sf::Packet sPacket2;
    std::map<std::string, Element*>::iterator it;

    Packet >> code;

    switch (code)
    {
        case NETWORK_NEW_CHARACTER:
            std::cout << "Welcome new character" << std::endl;
            sPacket2 << NETWORK_NEW_CHARACTER << currid;
            for (size_t i = 0; i < clients.size(); ++i)
            {
                if (client != clients[i].socket)
                {
                    sf::Packet sPacket3;
                    sPacket3 << NETWORK_NEW_CHARACTER << clients[i].id;
                    client.Send(sPacket3);
                    clients[i].socket.Send(sPacket2);
                }
                else
                    clients[i].id = currid;
            }
            sPacket << NETWORK_ID << currid;
            ++currid;
            client.Send(sPacket);
        break;
        case NETWORK_CHARACTER_MOVE:
            broadcast (Packet, &client);
        break;
        case NETWORK_ELEMENT_KEYBOARD_BOTTOM:
            broadcast (Packet, &client);
            Packet >> str;
            global_elements[str]->process_keyboard_other_bottom();
        break;
        case NETWORK_GLOBAL_ELEMENT:
            Packet >> str;
            std::cout << "Request element : <" << str << ">" << std::endl;
            if ((it = global_elements.find (str)) != global_elements.end ())
            {
                std::cout << "LITTLE DERP EXIST" << std::endl;
                it->second->sendPacket(client);
            }
            else
            {
              size_t ko = 0;
              size_t l = 0;
              std::string world_map;
              std::string xmap;
              std::string ymap;
              std::string object;
              l = str.find_first_of("#");
              world_map = str.substr(0, l);
              while (l != std::string::npos)
              {
                std::string tmp;
                size_t k = l;
                l = str.find_first_of("#", l + 1);
                if (l == std::string::npos)
                    tmp = str.substr(k + 1, l - k - 1);
                else
                    tmp = str.substr(k + 1, l - k - 1);
                switch (ko)
                {
                    case 0:
                        xmap = tmp;
                    break;
                    case 1:
                        ymap = tmp;
                    break;
                    case 2:
                        object = tmp;
                    break;
                }
                ++ko;
              }
              if (object == "chest")
              {
                  global_elements.insert (std::pair<std::string, Element*>(str, new Chest (atoi (xmap.c_str()), atoi (ymap.c_str()), str, "")));
              }

            }
        break;
        default:
            std::cerr << "Unknown code (" << code << ")" << std::endl;
        break;
    }
}

int main ()
{
  if (!Listener.Listen(2012))
  {
    std::cerr << "Binding to port 2012 failed" << std::endl;
    return 1;
  }
  Selector.Add(Listener);
  std::cout << "Server launch..." << std::endl;
  while (true)
  {
      unsigned int nsock = Selector.Wait();
      for (size_t i = 0; i < nsock; ++i)
      {
            sf::SocketTCP Socket = Selector.GetSocketReady(i);;

            if (Socket == Listener)
            {
                sf::IPAddress Address;
                sf::SocketTCP client;
                Listener.Accept(client, &Address);
                std::cout << "Client connected ! (" << Address << ")" << std::endl;
                Selector.Add(client);
                Client c1;
                c1.socket = client;
                c1.id = currid;
                clients.push_back (c1);
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
                    /*
                    for (std::vector<sf::SocketTCP>::iterator it = clients.begin();
                         it != clients.end();
                         it++)
                         {
                             if (Socket == (*it))
                                clients.erase(it);
                         }
                    */
                    for (std::vector<Client>::iterator it = clients.begin();
                          it != clients.end(); it++)
                    {
                        if (it->socket == Socket)
                        {
                            sf::Packet sPacketd;
                            sPacketd << NETWORK_DISCONNECT << it->id;
                            broadcast (sPacketd, &Socket);
                        }
                    }

                    Selector.Remove(Socket);

                }
            }
      }
  }
  return 0;
}
