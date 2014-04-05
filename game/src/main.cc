#include "game/game.hh"
#include "option/option.hh"
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>

Game* g;
Option* opt;
sf::RenderWindow* app;
MemoryManager<sf::Image>* img_mng;
bool g_display = true;

void listen_server (void* data);
void listen_server (void* data)
{
    sf::Clock clock;
    int n;
    int id;
    int x;
    int y;
    int dir;
    std::string str;
    sf::Packet sPacket;

    (void)data;
    sPacket << NETWORK_NEW_CHARACTER;
    g->Socket.Send(sPacket);
    while (app->IsOpened())
    {
        if (clock.GetElapsedTime() * 1000 > (1000 / opt->fps))
        {
            sf::Packet Packet;
            int code;
            g->Socket.Receive(Packet);
            Packet >> code;
            switch (code)
            {
                case NETWORK_NEW_CHARACTER:
                    Packet >> n;
                    std::cout << "A new player on the server id = "
                              << n
                              << std::endl;
                    if (g->player->id >= 0)
                        g->player->share_position();
                    g->characters.insert (std::pair<int, Character*>(n, new Character()));
                break;
                case NETWORK_CHARACTER_MOVE:
                    Packet >> n; //id
                    id = n;
                    Packet >> g->characters[id]->xmap; //g->xmap
                    Packet >> g->characters[id]->ymap; //g->ymap
                    Packet >> x; //animation->GetPosition().x
                    Packet >> y; //animation->GetPosition().y
                    Packet >> dir;
                    g->characters[id]->animation->setAnimRow(dir);

                    if (g->characters[id]->animation->currentFrame() + 1 >= g->characters[id]->animation->getSize())
                        g->characters[id]->animation->setFrame(0);
                    else
                        g->characters[id]->animation->setFrame(g->characters[id]->animation->currentFrame() + 1);
                    g->characters[id]->animation->SetPosition (x, y);
                break;
                case NETWORK_ID:
                    Packet >> n;
                    g->player->id = n;
                    g->player->share_position ();
                break;
                case NETWORK_DISCONNECT:
                    Packet >> n;
                    g->characters.erase(n);
                break;
                default:
                    std::cerr << "ERR CODE NOT HANDLE ("
                              << code << ")"
                              << std::endl;
                break;
            }

            clock.Reset ();
        }
        else
            sf::Sleep((1.0/ (float)opt->fps) - clock.GetElapsedTime());

    }
}

int main ()
{
  sf::Clock clock;
  sf::VideoMode vm = sf::VideoMode::GetDesktopMode();
  sf::Thread tr (listen_server);

  img_mng = new MemoryManager<sf::Image>;
  //app = new sf::RenderWindow(vm, "Nost ego", sf::Style::Fullscreen);
  app = new sf::RenderWindow(vm, "Nost ego");
  opt = new Option;
  g = new Game;
  g->init_game ();

  clock.Reset ();
  tr.Launch ();
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
  tr.Terminate ();
  delete g;
  delete opt;
  delete img_mng;

  return 0;
}
