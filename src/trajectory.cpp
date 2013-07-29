#include "SDL_gfxPrimitives.h"

#include "trajectory.hpp"
#include "importsettings.hpp"

Trajectory::Trajectory(SDL_Surface* screen) {
  this->screen = screen;
  lineColorRate = import::getLineColorRate();
  entries = 0;
}

void Trajectory::addPoint(double x, double y) {
  this->x[entries] = x;
  this->y[entries] = y;
  entries++;
}

void Trajectory::draw() {
  for (int i = 0; i < entries-1; i++) {
    aalineRGBA(screen, x[i], y[i], x[i+1], y[i+1], (cos(i/lineColorRate)+1)*255/2.0, (sin(i/lineColorRate)+1)*255/2.0, 0, 255);
  }
}
