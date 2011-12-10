#include <SFML/LayerAnim.hh>

LayerAnim::LayerAnim(float delay_p) :
    Anim (delay_p)
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
