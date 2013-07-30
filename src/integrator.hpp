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
  Integrator(Environment* environment, double *x0, double *para, int dimx, int dimpar, double stepsize);
  double* integrate(double tend);
  void setIntSettings(double h, int dimx, int dimpar);
  void setStepSize(double hin);
  void setState(double *px0);
  void setParameters(double *ppar);
  void updateState();

private:
  double x0[10], x1[10];
  double para[10];
  double *px0, *px1;
  double k1[10],k2[10],k3[10],k4[10];
  double x0k1[10], x0k2[10], x0k3[10];
  double h, tend, mu;
  double force1[10], force2[10], force3[10], force4[10];
  double *pforce1, *pforce2, *pforce3, *pforce4;
  int steps, dimx, dimpar;
  double time;

  Environment* environment;

  void oneStep();
};

#endif /*INTEGRATOR_H_*/
