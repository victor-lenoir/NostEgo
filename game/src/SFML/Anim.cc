#include <SFML/Anim.hh>
#include <iostream>

Anim::Anim(float delay_p) : m_time()
{
   m_frameCount=0;
   m_delay=delay_p;
   m_isLoop=true;
   m_play=true;
   once=false;
}

Anim::~Anim(void)
{
}

void Anim::nextFrame()
{
   if(currentFrame()==getSize()-1)
   {
      setFrame(0);
      if(!isLoop())
        stop();
   }
   else
      setFrame(currentFrame()+1);
}

void Anim::setFrame(const unsigned int &count)
{
   if(count<getSize())
      m_frameCount=count;
   else
      m_frameCount=0;
}

void Anim::reset()
{
   stop();
   play();
}

void Anim::loop(const bool &choice)
{
   m_isLoop=choice;
}

void Anim::play()
{
   m_play = true;
   m_time.Play();
}

void Anim::stop()
{
   Anim::m_play = false;
   setFrame(0);
   m_time.Stop();
}

void Anim::pause()
{
   Anim::m_play = false;
   m_time.Pause();
}

bool Anim::isPlaying() const
{
   return m_play;
}

void Anim::setDelay(const float &delay_p)
{
   m_delay = delay_p;
}

float Anim::delay() const
{
   return m_delay;
}

unsigned int Anim::currentFrame() const
{
   return m_frameCount;
}

bool Anim::isLoop() const
{
   return m_isLoop;
}

void Anim::update()
{
   if(isPlaying())
   {
      if(delay() > 0.0)
      {
	     unsigned int frameCount = (unsigned int)(m_time.GetElapsedTime()/delay());
	     if (once && (frameCount > getSize() - 1))
            {
             stop();
             setFrame(getSize() - 1);
            }
         else if(!isLoop() && frameCount>getSize())
            stop();
         else
         {
            frameCount = frameCount % getSize();
            setFrame(frameCount);
         }
      }
   }
}
