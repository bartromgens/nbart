#include "integrator.hpp"


Integrator::Integrator(Environment* environment, const std::array<double, 4>& x0)
  : m_environment(environment),
    x0(x0),
    x1(),
    px0(),
    px1()
{
}


Integrator::~Integrator()
{
  std::cout << "Integrator::~Integrator()" << std::endl;
}


const std::array<double, 4>&
Integrator::integrate(double tEnd, double stepsize)
{
  int steps = tEnd/std::fabs(stepsize);

  for (int i = 0; i < steps; i++)
  {
    oneStep(stepsize);
    updateState();
  }

  return x0;
}


void
Integrator::oneStep(double stepsize)
{
  pforce1 = m_environment->getStateDerivative(x0);
  for (std::size_t j = 0; j < x0.size(); j++)
  {
    k1[j] = stepsize * pforce1[j];
    x0k1[j] = x0[j] + 1./2.* k1[j]; // used in next step
  }

  pforce2 = m_environment->getStateDerivative(x0k1);
  for (std::size_t j = 0; j < x0.size(); j++)
  {
    k2[j] = stepsize * pforce2[j];
    x0k2[j] = x0[j] + 1./2.* k2[j]; // used in next step
  }

  pforce3 = m_environment->getStateDerivative(x0k2);
  for (std::size_t j = 0; j < x0.size(); j++)
  {
    k3[j] = stepsize * pforce3[j];
    x0k3[j] = x0[j] + k3[j]; // used in next step
  }

  pforce4 = m_environment->getStateDerivative(x0k3);

  for (std::size_t j = 0; j < x0.size(); j++)
  {
    k4[j] = stepsize * pforce4[j];
  }

  for (std::size_t i = 0; i < x0.size(); i++)
  {
    x1[i] = x0[i] + 1.0/6.0 * (k1[i]+2*k2[i]+2*k3[i]+k4[i]);
  }
}


void
Integrator::updateState()
{
  x0 = x1;
}
