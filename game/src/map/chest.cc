#include "chest.hh"
#include "../option/option.hh"
#include <game/game.hh>

Chest::Chest (int x, int y, std::ifstream& input, std::string hash)
  : Element ("chest", x, y, 1)
{
  std::string object;

  animation->pause ();
  animation->once = true;
  input >> object;
  set_global(hash);
  open = false;
}

void Chest::affect (sf::Packet& packet)
{
    std::string tmp;

    packet >> tmp;
    std::cout << "AFFECT = <" << tmp << ">" << std::endl;
    open = (tmp == "open");
    if (open)
        animation->play();
}

void Chest::sendPacket (sf::SocketTCP& client)
{
    sf::Packet packet;

    if (open)
        packet << NETWORK_GLOBAL_ELEMENT << hash_ << "open";
    else
        packet << NETWORK_GLOBAL_ELEMENT << hash_ << "closed";
    client.Send(packet);
}

Chest::Chest (int x, int y, std::string hash, std::string object)
{
  (void)x;
  (void)y;
  hash_ = hash;
  (void)object;
  open = false;
}

void Chest::process_keyboard_other_bottom ()
{
    if ((!open))
      {
        animation->play ();
        open = true;
      }
}

void Chest::process_keyboard_bottom ()
{
  if ((!open) && (app->GetInput().IsKeyDown (sf::Key::Space)))
  {
    sf::Packet sPacket;
    sPacket << NETWORK_ELEMENT_KEYBOARD_BOTTOM << hash_;
    g->Socket.Send(sPacket);
    animation->play ();
    open = true;
  }
}
