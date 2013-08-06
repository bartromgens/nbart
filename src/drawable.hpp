#ifndef DRAWABLE_H_
#define DRAWABLE_H_

#include <iostream>
#include <fstream>

#include "SDL/SDL.h"
#include "SDL_rotozoom.h"


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
