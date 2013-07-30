#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_

#include <vector>

#include "body.hpp"

//!  RK4 (Runge Kutta 4th order) fixed stepsize integrator class
/*!
   The most basic and conventional higher order RK4 ODE integrator.
   A RK4 object is composed of a EOMrk equations of motion object.
   A pointer to this EOMrk object is passed as parameter.
*/
class Environment {
public:
  Environment(SDL_Surface* m_screen);
  ~Environment();

  void addBody(Body* body);
  void addMasslessBody(Body* body);
  void mergeBodies();
  void clearAllBodies();

  void oneStep();

  void drawBodies();
  void drawTrajectories();

  double* getStateDerivative(double* x0, double* para);

  double getFieldStrength(double x, double y);
  double getEnergy();
  double getLinearMomentum();

protected:

private:
  SDL_Surface* m_screen;
  std::vector<Body*> m_bodies;
  std::vector<Body*> m_masslessBodies;
  int hres, vres;
  int m_nBodies;
};

#endif /* ENVIRONMENT_H_ */
