#include "integrator.hpp"

using namespace std;

Integrator::Integrator(Environment* environment, double* x0, double* para, int dimx, int dimpar, double stepsize) {
  setIntSettings(stepsize, dimx, dimpar);
  setState(x0);
  setParameters(para);
  this->environment = environment;
}

double* Integrator::integrate(double tend) {
  steps = tend/h;

  for (int i = 0; i < steps; i++) {
    oneStep();
    updateState();
  }
  return x0;
}

void Integrator::oneStep() {
  pforce1 = environment->getStateDerivative(x0, para);
  for (int j = 0; j < dimx; j++) {
    k1[j] = h * pforce1[j];
    x0k1[j] = x0[j] + 1./2.* k1[j]; // used in next step
  }
  pforce2 = environment->getStateDerivative(x0k1, para);
  for (int j = 0; j < dimx; j++) {
    k2[j] = h * pforce2[j];
    x0k2[j] = x0[j] + 1./2.* k2[j]; // used in next step
  }
  pforce3 = environment->getStateDerivative(x0k2, para);
  for (int j = 0; j < dimx; j++) {
    k3[j] = h * pforce3[j];
    x0k3[j] = x0[j] + k3[j]; // used in next step
  }
  pforce4 = environment->getStateDerivative(x0k3, para);
  for (int j = 0; j < dimx; j++) {
    k4[j] = h * pforce4[j];
  }
  for (int i = 0; i < dimx; i++) {
    x1[i] = x0[i] + 1./6. * (k1[i]+2*k2[i]+2*k3[i]+k4[i]);
  }
}

void Integrator::updateState() {
  for (int j = 0; j < dimx; j++) {
    x0[j] = x1[j];
  }
}

void Integrator::setIntSettings(double hin,  int dimxin, int dimparin) {
  h = hin;
  dimx = dimxin;
  dimpar = dimparin;
}

void Integrator::setState(double *state) {
  for (int i = 0; i < dimx; i++) {
    x0[i] = state[i];
  }
}

void Integrator::setParameters(double *pparin) {
  for (int i = 0; i < dimpar; i++) {
    para[i] = pparin[i];
  }
}

void Integrator::setStepSize(double hin) {
  h = hin;
}
