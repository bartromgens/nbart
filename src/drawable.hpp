#ifndef DRAWABLE_H_
#define DRAWABLE_H_

#include <iostream>
#include <fstream>

#include "SDL/SDL.h"
#include "SDL_rotozoom.h"

//!  RK4 (Runge Kutta 4th order) fixed stepsize integrator class
/*!
   The most basic and conventional higher order RK4 ODE integrator.
   A RK4 object is composed of a EOMrk equations of motion object.
   A pointer to this EOMrk object is passed as parameter.
*/
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
  SDL_Surface* drawablesurf;
  SDL_Surface* drawablezoomsurf;
  SDL_Surface* screen;
  int midx, midy;
  std::string imageloc;

  SDL_Rect pos, center;
};

#endif /* DRAWABLE_H_ */
