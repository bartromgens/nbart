#include "integrator.hpp"


Integrator::Integrator(Environment* environment, const std::array<double, 4>& x0)
  : m_environment(environment),
    x(x0)
{
}


Integrator::~Integrator()
{
//  std::cout << "Integrator::~Integrator()" << std::endl;
}


const std::array<double, 4>&
Integrator::integrate(double stepsize)
{
  oneStep(stepsize);

  return x;
}


void
Integrator::setEnvironment(Environment* environment)
{
  m_environment = environment;
}


void
Integrator::oneStep(double stepsize)
{
  std::array<double, 4> force = m_environment->getStateDerivative(x);
  for (std::size_t j = 0; j < x.size(); j++)
  {
    k1[j] = stepsize * force[j];
    x0k1[j] = x[j] + 1./2.* k1[j]; // used in next step
  }

  force = m_environment->getStateDerivative(x0k1);
  for (std::size_t j = 0; j < x.size(); j++)
  {
    k2[j] = stepsize * force[j];
    x0k2[j] = x[j] + 1./2.* k2[j]; // used in next step
  }

  force = m_environment->getStateDerivative(x0k2);
  for (std::size_t j = 0; j < x.size(); j++)
  {
    k3[j] = stepsize * force[j];
    x0k3[j] = x[j] + k3[j]; // used in next step
  }

  force = m_environment->getStateDerivative(x0k3);

  for (std::size_t j = 0; j < x.size(); j++)
  {
    k4[j] = stepsize * force[j];
  }

  for (std::size_t i = 0; i < x.size(); i++)
  {
    x[i] = x[i] + 1.0/6.0 * (k1[i]+2*k2[i]+2*k3[i]+k4[i]);
  }
}
