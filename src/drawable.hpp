#ifndef DRAWABLE_H_
#define DRAWABLE_H_

#include <iostream>
#include <fstream>

#include "SDL/SDL.h"
#include "SDL_rotozoom.h"

#include <QPoint>


class Drawable
{
public:
  Drawable(SDL_Surface* screen, std::string imageloc);
  ~Drawable();
  void loadSurface(std::string imageloc);
  void draw();

  void setTopLeftPos();
  void setCenterPos(int x, int y);
  void moveCenterPos(int dx, int dy);
  void setSize(int w);

private:
  SDL_Surface* m_drawablesurf;
  SDL_Surface* m_drawablezoomsurf;
  SDL_Surface* m_screen;

  SDL_Rect m_pos;
  QPoint m_center;
};

#endif /* DRAWABLE_H_ */
