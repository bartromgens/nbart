#include "drawable.hpp"
#include "integrator.hpp"
#include "environment.hpp"
#include "importsettings.hpp"

#include "body.hpp"

#include <cassert>

std::size_t Body::m_bodyIds = 0;

Body::Body(std::string imageloc)
  : m_x(),
    m_para(),
    m_integrator(),
    m_environment(0),
    m_nSteps(0),
    m_linerate(import::getLineRate()),
    m_id(m_bodyIds)
{
  m_bodyIds++;

  m_x[0] = 200.0;
  m_x[1] = 200.0;
  m_x[2] = 0;
  m_x[3] = 0;

  m_para[0] = .1e1; // mass [kg]
  m_para[1] = 15.0; // radius [m]
}


Body::~Body()
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}


void
Body::setEnvironment(Environment* environment)
{
  m_environment = environment;
  if (m_integrator)
  {
    m_integrator->setEnvironment(environment);
  }
  else
  {
    m_integrator.reset(new Integrator(m_environment, m_x));
  }
}


int
Body::getId() const
{
  return m_id;
}


void
Body::oneStep(double stepsize)
{
  assert(m_integrator);
  m_x = m_integrator->integrate(stepsize);
  m_nSteps++;
}


void
Body::setPosition(double xin, double yin)
{
  m_x[0] = xin;
  m_x[1] = yin;
  assert(m_environment);
  m_integrator.reset(new Integrator(m_environment, m_x));
//  setScreenCenterPos((int)m_x[0],(int)m_x[1]);
}


void
Body::setVelocity(double vxin, double vyin)
{
  m_x[2] = vxin;
  m_x[3] = vyin;
  assert(m_environment);
  m_integrator.reset(new Integrator(m_environment, m_x));
}


void
Body::setMass(double mass)
{
  m_para[0] = mass;
}


void
Body::setRadius(double radius)
{
  m_para[1] = radius;
}


double
Body::getMass() const
{
  return m_para[0];
}


const std::array<double, 4>&
Body::getState() const
{
  return m_x;
}


const std::array<double, 2>&
Body::getParameters() const
{
  return m_para;
}


double
Body::random(double start, double end)
{
  double randomDouble = start+(end-start)*rand()/(RAND_MAX + 1.0);
  return randomDouble;
}

