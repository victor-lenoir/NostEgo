#include <SFML/ImgAnim.hh>

ImgAnim::ImgAnim(float delay_p, sf::Image* Img, const unsigned int &nbFrame, const unsigned int &line,
		 const sf::Vector2f &Position, const sf::Vector2f &Scale_p,float Rotation, const sf::Color &Col)
  : Anim (delay_p), sf::Sprite(*Img,Position,Scale_p,Rotation,Col)
{
   m_animRow=0;
   Img_ = Img;
   //Le constructeur par défaut prend en compte qu'il n'y a aucun offset
   SetSubRect(sf::IntRect(0,0,Img->GetWidth()/nbFrame,Img->GetHeight()/line));
   m_xOffset=0;
   m_yOffset=0;
   m_size=nbFrame;
}

ImgAnim::~ImgAnim ()
{
  delete Img_;
}
void ImgAnim::setAnimRow(const unsigned int &row)
{
   m_animRow=row;
   refreshSubRect();
}

int ImgAnim::animRow() const
{
   return m_animRow;
}

void ImgAnim::setFrameDim(const unsigned int &w, const unsigned int &h)
{
   sf::IntRect tRect = GetSubRect();
   SetSubRect(sf::IntRect(tRect.Left,tRect.Top,tRect.Left+w,tRect.Top+h));
}

sf::IntRect ImgAnim::frameDim() const
{
   sf::IntRect tRect = GetSubRect();
   return sf::IntRect(0,0,tRect.GetWidth(),tRect.GetHeight());
}

void ImgAnim::setOffset(const unsigned int &x, const unsigned int &y)
{
   m_xOffset=x;
   m_yOffset=y;

   refreshSubRect();
}

sf::IntRect ImgAnim::offset() const
{
   return sf::IntRect(0,0,m_xOffset,m_yOffset);
}

int unsigned ImgAnim::getSize() const
{
   return m_size;
}

void ImgAnim::setSize(const unsigned int &size)
{
   m_size=size;
}


void ImgAnim::setFrame(const unsigned int &count)
{
   Anim::setFrame(count);
   refreshSubRect();
}

void ImgAnim::refreshSubRect()
{
   sf::IntRect tRect = GetSubRect();
   SetSubRect(sf::IntRect(tRect.GetWidth()*currentFrame()+m_xOffset,
			  tRect.GetHeight()*m_animRow+m_yOffset,
			  tRect.GetWidth()*(currentFrame()+1)+m_xOffset,
			  tRect.GetHeight()*m_animRow+tRect.GetHeight()+m_yOffset));
}


void ImgAnim::Render(sf::RenderTarget& Target) const
{
   ImgAnim* th = const_cast<ImgAnim*>(this);
   th->update();
   sf::Sprite::Render(Target);
}
