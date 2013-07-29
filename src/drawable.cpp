#include "drawable.hpp"
#include "globfunctions.hpp"


Drawable::Drawable(SDL_Surface* screen, std::string imageloc)
{
  this->screen = screen;
  center.x = 0;
  center.y = 0;

  loadSurface(imageloc);
  drawablezoomsurf = rotozoomSurface(drawablesurf, 0.0, 1, 1);
  pos.w = drawablezoomsurf->w;
  pos.h = drawablezoomsurf->h;

  setTopLeftPos();
}


Drawable::~Drawable()
{
  SDL_FreeSurface(drawablesurf);
  SDL_FreeSurface(drawablezoomsurf);
}


void
Drawable::draw()
{
  setTopLeftPos();
  SDL_BlitSurface(drawablezoomsurf, NULL, screen, &pos);
}


void
Drawable::loadSurface(std::string imageloc)
{
  drawablesurf = gf::load_image( imageloc , true );
}


void
Drawable::setTopLeftPos()
{
  pos.x = center.x - pos.w*0.5;
  pos.y = center.y - pos.h*0.5;
}


void
Drawable::setCenterPos(int x, int y)
{
  center.x = x;
  center.y = y;
}


void
Drawable::moveCenterPos(int dx, int dy)
{
  setCenterPos(center.x + dx, center.y + dy);
}


void
Drawable::setSize(int w)
{
  double zoomfac = (double)w/pos.w;
  drawablezoomsurf = rotozoomSurface(drawablesurf, 0.0, zoomfac, 1);
}
