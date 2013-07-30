#ifndef INTEGRATOR_H_
#define INTEGRATOR_H_

#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <fstream>

#include "environment.hpp"

//!  RK4 (Runge Kutta 4th order) fixed stepsize integrator class
/*!
   The most basic and conventional higher order RK4 ODE integrator.
   A RK4 object is composed of a EOMrk equations of motion object.
   A pointer to this EOMrk object is passed as parameter.
*/
class Integrator
{
public:
  Integrator(Environment* m_environment, const std::array<double, 4>& x0, double stepsize);
  std::array<double, 4> integrate(double m_tEnd);
  void setStepSize(double hin);

  void updateState();

private:
  void oneStep();

private:
  Environment* m_environment;

  double m_stepsize;
  double m_tEnd;

  std::array<double, 4> x0;
  std::array<double, 4> x1;

  std::array<double, 4> px0;
  std::array<double, 4> px1;

  std::array<double, 4> x0k1;
  std::array<double, 4> x0k2;
  std::array<double, 4> x0k3;

  std::array<double, 4> k1;
  std::array<double, 4> k2;
  std::array<double, 4> k3;
  std::array<double, 4> k4;

  std::array<double, 4> pforce1;
  std::array<double, 4> pforce2;
  std::array<double, 4> pforce3;
  std::array<double, 4> pforce4;

  int m_steps;
};

#endif /*INTEGRATOR_H_*/
