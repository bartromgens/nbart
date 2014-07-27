#ifndef BODY_H_
#define BODY_H_

#include <array>
#include <memory>
#include <iostream>
#include <vector>

#include "SDL/SDL.h"
#include "trajectory.hpp"

#include "drawable.hpp"

class Integrator;
class Environment;

class Body
{
public:
  Body(std::string imageloc);
  ~Body();

  int getId() const;

  void oneStep(double stepsize);

  void setPosition(double m_x, double y);
  void setVelocity(double vxin, double vyin);

  void setMass(double mass);
  void setRadius(double radius);

  double getMass() const;
  const std::array<double, 4>& getState() const;
  const std::array<double, 2>& getParameters() const;

  void setEnvironment(Environment* environment);

private:
  static double random(double start, double end);

private:
  std::array<double, 4> m_x;
  std::array<double, 2> m_para; // {mass, radius}

  std::unique_ptr<Integrator> m_integrator;
  Environment* m_environment;

  int m_nSteps;
  int m_linerate;
  int m_id;

  static std::size_t m_bodyIds;
};

#endif /* BODY_H_ */
