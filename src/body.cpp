#include "drawable.hpp"
#include "integrator.hpp"
#include "environment.hpp"
#include "importsettings.hpp"

#include "body.hpp"

Body::Body(Environment* environment, SDL_Surface *screen, std::string imageloc)
  : m_x(),
    m_xNew(),
    m_para(),
    m_integrator(),
    m_environment(environment),
    m_trajectory(new Trajectory(screen)),
    m_drawable(new Drawable(screen, imageloc)),
    m_nSteps(0),
    m_linerate(import::getLineRate())
{
  m_x[0] = 200.0;
  m_x[1] = 200.0;
  m_x[2] = 0;
  m_x[3] = 0;

  m_para[0] = .1e1; // mass [kg]
  m_para[1] = 15.0; // radius [m]

  m_integrator.reset(new Integrator(m_environment, m_x));

  m_drawable->setSize(2*m_para[1]);

  setScreenCenterPos( static_cast<int>(m_x[0]), static_cast<int>(m_x[1]) );
}


Body::~Body()
{
}


void
Body::draw()
{
  m_drawable->draw();
}


void
Body::drawTrajectory()
{
  m_trajectory->draw();
}


void
Body::oneStep(double tEnd, double stepsize)
{
  m_xNew = m_integrator->integrate(tEnd, stepsize);
}


void
Body::updateState()
{
  m_x = m_xNew;

  if (m_nSteps%(10*m_linerate) == 0)
  {
    m_trajectory->addPoint(m_x[0],m_x[1]);
  }

  setScreenCenterPos((int)m_x[0],(int)m_x[1]);
  m_nSteps++;
}


void
Body::setPosition(double xin, double yin)
{
  m_x[0] = xin;
  m_x[1] = yin;
  m_integrator.reset(new Integrator(m_environment, m_x));
  setScreenCenterPos((int)m_x[0],(int)m_x[1]);
}


void
Body::setVelocity(double vxin, double vyin)
{
  m_x[2] = vxin;
  m_x[3] = vyin;
  m_integrator.reset(new Integrator(m_environment, m_x));
}


void
Body::setScreenCenterPos(int x, int y)
{
  m_drawable->setCenterPos(x,y);
}


void
Body::moveScreenCenterPos(int dx, int dy)
{
  m_drawable->moveCenterPos(dx, dy);
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
  m_drawable->setSize(2*m_para[1]);
}


double
Body::getMass()
{
  return m_para[0];
}


const std::array<double, 4>&
Body::getState()
{
  return m_x;
}


const std::array<double, 2>&
Body::getParameters()
{
  return m_para;
}


double
Body::random(double start, double end)
{
  double randomDouble = start+(end-start)*rand()/(RAND_MAX + 1.0);
  return randomDouble;
}

