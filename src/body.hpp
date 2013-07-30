#ifndef BODY_H_
#define BODY_H_

#include <array>
#include <iostream>
#include <vector>

#include "SDL/SDL.h"
#include "trajectory.hpp"

class DrawableBody;
class Integrator;
class Environment;

//!  RK4 (Runge Kutta 4th order) fixed stepsize integrator class
/*!
   The most basic and conventional higher order RK4 ODE integrator.
   A RK4 object is composed of a EOMrk equations of motion object.
   A pointer to this EOMrk object is passed as parameter.
*/

class Body {
public:
  Body(Environment* environment, SDL_Surface *screen, std::string imageloc);
  ~Body();

  void draw();
  void drawTrajectory();

  void oneStep();
  void updateState();

  void setPosition(double x, double y);
  void setVelocity(double vxin, double vyin);
  void setScreenCenterPos(int x, int y);
  void moveScreenCenterPos(int dx, int dy);

  void setMass(double mass);
  void setRadius(double radius);

  double getMass();
  const std::array<double, 4>& getState();
  const std::array<double, 2>& getParameters();
protected:

private:
  SDL_Surface* screen;
  Integrator* m_integrator;
  Environment* environment;
  Trajectory* trajectory;

  double stepsize;
  std::array<double, 4> x;
  std::array<double, 4> xNew;
  std::array<double, 2> para; // {mass, radius}
  int nStep;
  int linerate;

  DrawableBody *drawbody;

  double random(double start, double end);
};

#endif /* BODY_H_ */
