#include "integrator.hpp"

using namespace std;

Integrator::Integrator(Environment* environment, const std::array<double, 4> &x0, double stepsize)
  : m_environment(environment),
    m_stepsize(stepsize),
    x0(x0),
    x1(),
    px0(),
    px1()
{
}


const std::array<double, 4>&
Integrator::integrate(double tend)
{
  m_steps = tend/m_stepsize;

  for (int i = 0; i < m_steps; i++)
  {
    oneStep();
    updateState();
  }

  return x0;
}


void
Integrator::oneStep()
{
  pforce1 = m_environment->getStateDerivative(x0);
  for (std::size_t j = 0; j < x0.size(); j++)
  {
    k1[j] = m_stepsize * pforce1[j];
    x0k1[j] = x0[j] + 1./2.* k1[j]; // used in next step
  }

  pforce2 = m_environment->getStateDerivative(x0k1);
  for (std::size_t j = 0; j < x0.size(); j++)
  {
    k2[j] = m_stepsize * pforce2[j];
    x0k2[j] = x0[j] + 1./2.* k2[j]; // used in next step
  }

  pforce3 = m_environment->getStateDerivative(x0k2);
  for (std::size_t j = 0; j < x0.size(); j++)
  {
    k3[j] = m_stepsize * pforce3[j];
    x0k3[j] = x0[j] + k3[j]; // used in next step
  }

  pforce4 = m_environment->getStateDerivative(x0k3);

  for (std::size_t j = 0; j < x0.size(); j++)
  {
    k4[j] = m_stepsize * pforce4[j];
  }

  for (std::size_t i = 0; i < x0.size(); i++)
  {
    x1[i] = x0[i] + 1./6. * (k1[i]+2*k2[i]+2*k3[i]+k4[i]);
  }
}


void
Integrator::updateState()
{
  for (std::size_t j = 0; j < x0.size(); j++)
  {
    x0[j] = x1[j];
  }
}


void
Integrator::setStepSize(double hin)
{
  m_stepsize = hin;
}
