#include "drawable.hpp"
#include "globfunctions.hpp"


Drawable::Drawable(SDL_Surface* screen, std::string imageloc) :
  m_screen(screen),
  m_center(0, 0)
{

  loadSurface(imageloc);
  m_drawablezoomsurf = rotozoomSurface(m_drawablesurf, 0.0, 1, 1);
  m_pos.w = m_drawablezoomsurf->w;
  m_pos.h = m_drawablezoomsurf->h;

  setTopLeftPos();
}


Drawable::~Drawable()
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
  SDL_FreeSurface(m_drawablesurf);
  SDL_FreeSurface(m_drawablezoomsurf);
}


void
Drawable::draw()
{
  setTopLeftPos();
  SDL_BlitSurface(m_drawablezoomsurf, NULL, m_screen, &m_pos);
}


void
Drawable::loadSurface(std::string imageloc)
{
  m_drawablesurf = gf::load_image( imageloc , true );
}


void
Drawable::setTopLeftPos()
{
  m_pos.x = m_center.x() - m_pos.w*0.5;
  m_pos.y = m_center.y() - m_pos.h*0.5;
}


void
Drawable::setCenterPos(int x, int y)
{
  m_center.setX(x);
  m_center.setY(y);
}


void
Drawable::moveCenterPos(int dx, int dy)
{
  setCenterPos(m_center.x() + dx, m_center.y() + dy);
}


void
Drawable::setSize(int w)
{
  double zoomfac = (double)w/m_pos.w;
  m_drawablezoomsurf = rotozoomSurface(m_drawablesurf, 0.0, zoomfac, 1);
}
