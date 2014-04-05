#ifndef IMGANIM_H
#define IMGANIM_H

#include <SFML/Graphics.hpp>
#include <SFML/Anim.hh>

/*!
 *\class ImgAnim
 *Comme Anim à la diférence près que la classe utilise une image avec tout les sprites
 *au lieu des couches d'une layer.
 */
class ImgAnim :
   public Anim, public sf::Sprite
{
public:
   /*
    *\param img Image avec les sprites
    *\param rows Nombre de frame par animation
    *\param line Nombre de ligne d'animation
    *\param leReste Voir la documentation de sf::Sprite
    */
   ImgAnim(float delay_p, sf::Image* Img, const unsigned int &nbFrame, const unsigned int &line=1,
	   const sf::Vector2f &Position=sf::Vector2f(0, 0),
	   const sf::Vector2f &Scale=sf::Vector2f(1, 1), float Rotation=0.f,
	   const sf::Color &Col=sf::Color(255, 255, 255, 255));


   //!Définis les dimension d'un frame
   void setFrameDim(const unsigned int &w, const unsigned int &h);
   void play_once();
   //!Retourne la dimension d'un frame
   sf::IntRect frameDim() const;

   //!Définis le décalage de l'animation sur l'image (permet d'avoir plusieurs anim sur une seule image)
   void setOffset(const unsigned int &x, const unsigned int &y);

   //!Retourne un rectangle avec l'offset
   sf::IntRect offset() const;

   //!Définis la ligne animé courante
   void setAnimRow(const unsigned int &row);

   //!Retourne la ligne animé courante
   int animRow() const;

   //!Définis le frame courant
   virtual void setFrame(const unsigned int &count);

   //!Met à jour le rectangle d'animation
   void refreshSubRect();

   //!Définis le nombre de frame dans l'animation
   void setSize(const unsigned int &size);
  ~ImgAnim ();
   //!Retourne le nombre de frame
   virtual unsigned int getSize() const;
protected:
   virtual void Render(sf::RenderTarget& Target) const;

private:
   //!Représente le nombre de frame dans l'animation
  sf::Image* Img_;
   unsigned int m_size;
   //!Ligne d'animation courante
   unsigned int m_animRow;
   //!Décalage à gauche du frameset
   unsigned int m_xOffset;
   //!Décalage en haut du frameset
   unsigned int m_yOffset;
};

#endif
