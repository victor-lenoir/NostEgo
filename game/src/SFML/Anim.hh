#ifndef ANIM_H
#define ANIM_H

#include <SFML/System.hpp>
#include <SFML/PausableClock.hh>

/*!
 *\class Anim
 *Implémente la gestion des animation selon le temps.
 */
class Anim
{
  public:
   Anim(void);
   virtual ~Anim(void);

   //!Change au prochain frame d'animation
   void nextFrame();

   //!Change au frame d'animation défini par 'count'
   virtual void setFrame(const unsigned int &count);

   //!Change au premier frame animation
   void reset();

   //!Retourne le frame d'animation courante
   unsigned int currentFrame() const;


   //!Définis si l'animation est en boucle (choice=true)
   void loop(const bool &choice);

   //!Retourne si l'animation est joué en boucle
   bool isLoop() const;


   //!Joue l'animation
   void play();

   //!Arrete l'animation et remet le compteur à zéro
   void stop();

   //!Met l'animation en pause et laisse le compteur où il en est.
   void pause();

   //!Retourne true si l'animation joue
   bool isPlaying() const;

   //!Définis le délais en seconde entre chaque frame.
   void setDelay(const float &delay_p);

   //!Retourne le délai entre chaque frame
   float delay() const;

   //!Met à jour l'animation
   virtual void update();

   //!Retourne le nombre de frame de l'animation
   virtual unsigned int getSize() const=0;
  protected:
   //!Timer de l'animation
   PausableClock m_time;

  private:
   //!Frame courant de l'animation
   unsigned int m_frameCount;
   //!Delai en seconde entre chaque animation
   float m_delay;
   //!Si l'animation est en boucle
   bool m_isLoop;
   //!Si l'animation est en train de jouer
   bool m_play;
};

#endif
