
#include "importsettings.hpp"

#include "environment.hpp"

#include <cmath>
#include <cassert>
#include <functional>
#include <thread>


Environment::Environment(SDL_Surface* screen)
  : m_screen(screen),
    m_hres(import::getHres()),
    m_vres(import::getVres())
{
}


Environment::~Environment() {
}


void
Environment::addBody(Body* body)
{
  std::lock_guard<std::mutex> lock(m_mutex);
  printState();

  m_bodies.push_back(body);
}


void
Environment::addMasslessBody(Body* body)
{
  std::lock_guard<std::mutex> lock(m_mutex);
  printState();

  m_masslessBodies.push_back(body);
}


void
Environment::clearAllBodies()
{
  std::lock_guard<std::mutex> lock(m_mutex);
  printState();

  m_bodies.clear();
  m_masslessBodies.clear();
}


void
Environment::drawBodies()
{
  std::lock_guard<std::mutex> lock(m_mutex);

  for (std::size_t i = 0; i < m_bodies.size(); i++)
  {
    m_bodies[i]->draw();
  }
  for (std::size_t i = 0; i < m_masslessBodies.size(); i++)
  {
    m_masslessBodies[i]->draw();
  }
}


void
Environment::drawTrajectories()
{
  std::lock_guard<std::mutex> lock(m_mutex);

  for (std::size_t i = 0; i < m_bodies.size(); i++)
  {
    m_bodies[i]->drawTrajectory();
  }
}


void
Environment::oneStep(double tEnd, double stepsize)
{
  std::thread t(&Environment::oneStepImpl, this, tEnd, stepsize);
  t.detach();
}


void
Environment::oneStepImpl(double tEnd, double stepsize)
{
  std::lock_guard<std::mutex> lock(m_mutex);

  double stepsizeAbsolute = std::fabs(stepsize);
  if (stepsizeAbsolute < 1.0e-6)
  {
    std::cerr << "Environment::oneStepImpl() - ERROR: stepsize too small: " << stepsize << std::endl;
    return;
  }

  int steps = tEnd/stepsizeAbsolute;
  assert(steps >= 0);

  for (int i = 0; i < steps; ++i)
  {
    for (std::size_t i = 0; i < m_bodies.size(); i++)
    {
      m_bodies[i]->oneStep(stepsize);
    }
    for (std::size_t i = 0; i < m_masslessBodies.size(); i++)
    {
      m_masslessBodies[i]->oneStep(stepsize);
    }

    updateState();
  }
}


void
Environment::updateState()
{
  for (std::size_t i = 0; i < m_bodies.size(); i++)
  {
    m_bodies[i]->updateState();
  }

  for (std::size_t i = 0; i < m_masslessBodies.size(); i++)
  {
    m_masslessBodies[i]->updateState();
  }
}


const std::array<double, 4>&
Environment::getStateDerivative(const std::array<double, 4>& x)
{
  m_stateDerivative.fill(0.0);

//  m_stateDerivative[2] = 0.0;
//  m_stateDerivative[3] = 0.0;

  for (auto iter = m_bodies.begin(); iter != m_bodies.end(); iter++)
  {
    m_x2 = (*iter)->getState();
    if (m_x2[0] != x[0] && m_x2[1] != x[1])
    {
      double y12 = x[1]-m_x2[1];
      double x12 = x[0]-m_x2[0];
      double r = sqrt(x12*x12+y12*y12);
      if (r > 5)
      {
        double r3 = r*r*r;
        double mass = (*iter)->getMass();
        const double c = mass/r3;
        m_stateDerivative[2] -= c * x12;
        m_stateDerivative[3] -= c * y12;
      }
    }
  }

  m_stateDerivative[0] = x[2];
  m_stateDerivative[1] = x[3];

  return m_stateDerivative;
}


void
Environment::mergeBodies()
{
  double x12, y12, r12;
  bool localcol = false;
  double massNew, xNew, yNew, vxNew, vyNew;

  for (auto iter = m_bodies.begin(); iter != m_bodies.end();)
  {
    m_x1 = (*iter)->getState();
    m_para1 = (*iter)->getParameters();

    for (auto iter2 = m_bodies.begin(); iter2 != m_bodies.end();)
    {
      m_x2 = (*iter2)->getState();
      m_para2 = (*iter2)->getParameters();
      x12 = m_x2[0]-m_x1[0];
      y12 = m_x2[1]-m_x1[1];
      r12 = sqrt(x12*x12+y12*y12);

      if ( (iter2 != iter) && (r12 < (m_para1[1]+m_para2[1])) )
      {
        localcol = true;
        std::cout << "Collision" << std::endl;
        massNew = (m_para1[0]+m_para2[0]);
        xNew = (m_x1[0]*m_para1[0]+m_x2[0]*m_para2[0])/massNew;
        yNew = (m_x1[1]*m_para1[0]+m_x2[1]*m_para2[0])/massNew;
        vxNew = (m_para1[0]*m_x1[2]+m_para2[0]*m_x2[2]) / massNew;
        vyNew = (m_para1[0]*m_x1[3]+m_para2[0]*m_x2[3]) / massNew;

        iter2 = m_bodies.erase(iter2);
        break;
      }
      else
      {
        iter2++;
      }
    }

    if (localcol)
    {
      iter = m_bodies.erase(iter);
      break;
    }
    else
    {
      iter++;
    }
  }

  if (localcol)
  {
    Body* body = new Body(this, m_screen, "./data/blurball.png");
    body->setMass(massNew);
    body->setRadius(sqrt(massNew*20));
    body->setPosition(xNew, yNew);
    body->setVelocity(vxNew, vyNew);
    addBody(body);
    localcol = false;
  }
}


double
Environment::getFieldStrength(double x, double y)
{
  std::array<double, 4> x2;
  double r;
  double mass;
  double x12[2];
  double gravityForce = 0.0;
  double gravityForceX = 0.0;
  double gravityForceY = 0.0;

  for (auto iter = m_bodies.begin(); iter != m_bodies.end(); iter++)
  {
    x2 = (*iter)->getState();
    if (x2[0] != x && x2[1] != y)
    {
      mass = (*iter)->getMass();
      x12[0] = x-x2[0];
      x12[1] = y-x2[1];
      r = sqrt(x12[0]*x12[0]+x12[1]*x12[1]);
      if (r > 1)
      {
        gravityForceX += mass/(r*r*r)*x12[0];
        gravityForceY += mass/(r*r*r)*x12[1];
      }
    }
  }

  gravityForce = sqrt(pow(gravityForceX,2)+pow(gravityForceY,2));
  return gravityForce;
}


double
Environment::getEnergy()
{
  double energy;
  double kineticEnergy = 0.0;
  double potentialEnergy = 0.0;

  double x12, y12, r12;

  for (auto iter = m_bodies.begin(); iter != m_bodies.end(); iter++)
  {
    m_x1 = (*iter)->getState();
    m_para1 = (*iter)->getParameters();

    for (auto iter2 = m_bodies.begin(); iter2 != m_bodies.end(); iter2++)
    {
      if (iter2 != iter)
      {
        m_x2 = (*iter2)->getState();
        m_para2 = (*iter2)->getParameters();
        x12 = m_x2[0]-m_x1[0];
        y12 = m_x2[1]-m_x1[1];
        r12 = sqrt(x12*x12+y12*y12);

        potentialEnergy -= m_para1[0]*m_para2[0]/r12;
      }
    }
    kineticEnergy += 0.5*m_para1[0]*(m_x1[2]*m_x1[2]+m_x1[3]*m_x1[3]);
  }

  energy = 2*kineticEnergy + potentialEnergy;
  return energy;
}


double
Environment::getLinearMomentum()
{
  double linearMomentum = 0;

  for (auto iter = m_bodies.begin(); iter != m_bodies.end(); iter++)
  {
    m_x1 = (*iter)->getState();
    m_para1 = (*iter)->getParameters();
    linearMomentum += m_para1[0]*m_x1[2];
  }

  return linearMomentum;
}


void
Environment::printState() const
{
  std::cout << "Environment state:" << std::endl;
  std::cout << "bodies: " << m_bodies.size() << std::endl;
  std::cout << "massless bodies: " << m_masslessBodies.size() << std::endl;

}
