#ifndef INTEGRATOR_H_
#define INTEGRATOR_H_

#include <iostream>
#include <fstream>
#include <cmath>

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
  Integrator(Environment* m_environment, const std::vector<double>& x0, double stepsize);
  std::vector<double> integrate(double m_tEnd);
  void setStepSize(double hin);

  void updateState();

private:
  void oneStep();

private:
  Environment* m_environment;

  double m_stepsize;
  double m_tEnd;

  std::vector<double> x0;
  std::vector<double> x1;

  std::vector<double> px0;
  std::vector<double> px1;

  int m_steps;
};

#endif /*INTEGRATOR_H_*/
