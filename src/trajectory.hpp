#ifndef TRAJECTORY_H_
#define TRAJECTORY_H_

#include "SDL/SDL.h"

#include <iostream>
#include <vector>

class Trajectory
{
public:
  Trajectory(SDL_Surface* m_screen);

  void addPoint(double x, double y);
  void draw();

private:
  SDL_Surface* m_screen;
  double m_lineColorRate;
  std::vector<double> m_x;
  std::vector<double> m_y;
};

#endif /* TRAJECTORY_H_ */
