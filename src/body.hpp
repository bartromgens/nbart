#ifndef BODY_H_
#define BODY_H_

#include <array>
#include <memory>
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
  Body(Environment* m_environment, SDL_Surface *screen, std::string imageloc);
  ~Body();

  void draw();
  void drawTrajectory();

  void oneStep();
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
protected:

private:
  std::unique_ptr<Integrator> m_integrator;
  Environment* m_environment;
  std::unique_ptr<Trajectory> m_trajectory;
  std::unique_ptr<DrawableBody> m_drawable;

  double stepsize;
  std::array<double, 4> m_x;
  std::array<double, 4> m_xNew;
  std::array<double, 2> m_para; // {mass, radius}
  int nStep;
  int linerate;

  double random(double start, double end);
};

#endif /* BODY_H_ */
