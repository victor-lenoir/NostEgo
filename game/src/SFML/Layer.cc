#include <SFML/Layer.hh>
#include <iostream>

Layer::Layer(const sf::Vector2f& Position, const sf::Vector2f& Scale_p, float Rotation, const sf::Color& Col)
  : Drawable(Position,Scale_p,Rotation,Col)
{
}

Layer::~Layer()
{
}

void Layer::Render(sf::RenderTarget& Target) const
{
   // Let the derived class render the object geometry
   for( itFrame i = begin() ;i!=end();i++)
      Target.Draw(*(*i));
}
