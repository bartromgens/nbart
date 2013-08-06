#include "drawable.hpp"
#include "drawableBody.hpp"
#include "integrator.hpp"
#include "environment.hpp"
#include "importsettings.hpp"

#include "body.hpp"

Body::Body(Environment* environment, SDL_Surface *screen, std::string imageloc)
  : m_integrator(new Integrator(environment, m_x, stepsize)),
    m_environment(environment),
    m_trajectory(new Trajectory(screen)),
    m_drawable(new DrawableBody(screen, imageloc)),
    m_x(),
    m_xNew(),
    m_para()
{
  nStep = 0;
  stepsize = import::getStepSize();
  linerate = import::getLineRate();

  m_x[0] = 200.0;
  m_x[1] = 200.0;
  m_x[2] = 0;
  m_x[3] = 0;

  m_para[0] = .1e1; // mass [kg]
  m_para[1] = 15.0; // radius [m]

  m_drawable->setSize(2*m_para[1]);
  setScreenCenterPos((int)m_x[0],(int)m_x[1]);
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
Body::oneStep()
{
  m_xNew = m_integrator->integrate(1);
}


void
Body::updateState()
{
  m_x = m_xNew;

  if (nStep%(10*linerate) == 0)
  {
    m_trajectory->addPoint(m_x[0],m_x[1]);
  }

  setScreenCenterPos((int)m_x[0],(int)m_x[1]);
  nStep++;
}


void
Body::setPosition(double xin, double yin)
{
  m_x[0] = xin;
  m_x[1] = yin;
  m_integrator.reset(new Integrator(m_environment, m_x, stepsize));
  setScreenCenterPos((int)m_x[0],(int)m_x[1]);
}


void
Body::setVelocity(double vxin, double vyin)
{
  m_x[2] = vxin;
  m_x[3] = vyin;
  m_integrator.reset(new Integrator(m_environment, m_x, stepsize));
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

