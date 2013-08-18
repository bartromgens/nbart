#ifndef BODY_H_
#define BODY_H_

#include <array>
#include <memory>
#include <iostream>
#include <vector>

#include "SDL/SDL.h"
#include "trajectory.hpp"

class Drawable;
class Integrator;
class Environment;

class Body
{
public:
  Body(Environment* m_environment, SDL_Surface *screen, std::string imageloc);
  ~Body();

  void draw();
  void drawTrajectory();

  void oneStep(double stepsize);
  void updateState();

  void setPosition(double m_x, double y);
  void setVelocity(double vxin, double vyin);
  void setScreenCenterPos(int m_x, int y);
  void moveScreenCenterPos(int dx, int dy);

  void setMass(double mass);
  void setRadius(double radius);

  double getMass();
  const std::array<double, 4>& getState();
  const std::array<double, 2>& getParameters();

private:
  double random(double start, double end);

private:
  std::array<double, 4> m_x;
  std::array<double, 4> m_xNew;
  std::array<double, 2> m_para; // {mass, radius}

  std::unique_ptr<Integrator> m_integrator;
  Environment* m_environment;
  std::unique_ptr<Trajectory> m_trajectory;
  std::unique_ptr<Drawable> m_drawable;

  int m_nSteps;
  int m_linerate;
};

#endif /* BODY_H_ */
