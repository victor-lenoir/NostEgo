#ifndef SERVER_HH_
# define SERVER_HH_

# include <SFML/Network.hpp>

struct Character;
struct Client
{
  sf::SocketTCP socket;
  Character* c;
};

#endif // !SERVER_HH_
