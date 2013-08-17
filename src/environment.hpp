#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_

#include <array>
#include <mutex>
#include <vector>

#include "body.hpp"

class Environment {
public:
  Environment(SDL_Surface* m_screen);
  ~Environment();

  void addBody(Body* body);
  void addMasslessBody(Body* body);
  void mergeBodies();
  void clearAllBodies();

  void oneStep(double tEnd, double stepsize);

  void drawBodies();
  void drawTrajectories();

  std::array<double, 4> getStateDerivative(const std::array<double, 4> &x0);

  double getFieldStrength(double x, double y);
  double getEnergy();
  double getLinearMomentum();

protected:

private:
  void oneStepImpl(double tEnd, double stepsize);
  void updateState();

private:
  SDL_Surface* m_screen;
  std::vector<Body*> m_bodies;
  std::vector<Body*> m_masslessBodies;
  int hres, vres;
  int m_nBodies;

  std::array<double, 4> x1;
  std::array<double, 4> x2;

  std::array<double, 2> para1;
  std::array<double, 2> para2;

//  std::array<double, 4> stateDerivative;

  mutable std::mutex m_mutex;
};

#endif /* ENVIRONMENT_H_ */
