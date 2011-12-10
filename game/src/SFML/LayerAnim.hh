#ifndef LAYERANIM_H
#define LAYERANIM_H

#include <SFML/Anim.hh>
#include <SFML/Layer.hh>

/*
 *Animation où chaque frame est repésenter par une couche de Layer.
 */
class LayerAnim :
   public Anim, public Layer
{
public:
   LayerAnim(float delay_p);

   //!Retourne le nombre de frame de l'animation
   virtual unsigned int getSize() const;

protected:
   virtual void Render(sf::RenderTarget& Target) const;
};

#endif
