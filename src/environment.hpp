#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_

#include <array>
#include <list>
#include <mutex>
#include <vector>
#include <thread>

#include "body.hpp"

class Environment {
public:
  Environment(SDL_Surface* m_screen);
  ~Environment();

  void addBody(Body* body);
  void removeBody(Body* body);
  void addMasslessBody(Body* body);
  const std::list<Body*>& getBodies() const;

//  void mergeBodies();
  void clearAllBodies();

  void oneStep(double tEnd, double stepsize);

  std::array<double, 4> getStateDerivative(const std::array<double, 4>& x0);

  double getFieldStrength(double x, double y);
  double getEnergy();
  double getLinearMomentum();

  void printState() const;

protected:

private:
  void oneStepImpl(double tEnd, double stepsize);

private:
  SDL_Surface* m_screen;
  std::list<Body*> m_bodies;
  std::vector<Body*> m_masslessBodies;
  int m_hres;
  int m_vres;

  std::array<double, 4> m_x1;
  std::array<double, 4> m_x2;

  std::array<double, 2> m_para1;
  std::array<double, 2> m_para2;

//  std::array<double, 4> m_stateDerivative;

  mutable std::mutex m_mutex;

  std::thread* m_thread;
  unsigned int m_nStep;
  unsigned int m_nStepReal;
};

#endif /* ENVIRONMENT_H_ */
