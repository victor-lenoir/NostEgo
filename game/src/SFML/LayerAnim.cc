#include <SFML/LayerAnim.hh>

LayerAnim::LayerAnim(void)
{
}


unsigned int LayerAnim::getSize() const
{
   return size();
}

void LayerAnim::Render(sf::RenderTarget& Target) const
{
   Anim* th = const_cast<LayerAnim*>(this);
   th->update();
   Target.Draw(*at(currentFrame()));
}
