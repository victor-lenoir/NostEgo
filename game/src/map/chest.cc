#include "chest.hh"
#include "../option/option.hh"
#include <game/game.hh>

Chest::Chest (int x_, int y_, std::ifstream& input, int id_)
  : Element ("chest", x_, y_, 1, id_)
{
  stop_animation = true;
  input >> object;
  open = false;
}

void Chest::open_chest() {
  open = true;
  load_animation();
  animation->once = true;
  animation->play();
}

void Chest::update(sf::Packet& packet) {
  if (open)
    packet << NETWORK_CHEST_IS_OPEN << id;
}

void Chest::process_keyboard_bottom (Character* p) {
  bool space = p->is_key_down(sf::Key::Space);

  if ((!open) && space) {
    sf::Packet sPacket;

    sPacket << NETWORK_CHEST
            << object
            << p->id
            << id;
    p->broadcast_local(sPacket);
    open = true;
  }
}
