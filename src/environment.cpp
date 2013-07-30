#include <cmath>

#include "importsettings.hpp"

#include "environment.hpp"


Environment::Environment(SDL_Surface* screen)
  : m_screen(screen),
    hres(import::getHres()),
    vres(import::getVres()),
    m_nBodies(import::getNBodies())
{
}


Environment::~Environment() {
}


void
Environment::addBody(Body* body)
{
  m_bodies.push_back(body);
}


void
Environment::addMasslessBody(Body* body)
{
  m_masslessBodies.push_back(body);
}


void
Environment::clearAllBodies()
{
  m_bodies.clear();
  m_masslessBodies.clear();
}


void
Environment::drawBodies()
{
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
  for (std::size_t i = 0; i < m_bodies.size(); i++)
  {
    m_bodies[i]->drawTrajectory();
  }
}


void
Environment::oneStep()
{
  for (std::size_t i = 0; i < m_bodies.size(); i++)
  {
    m_bodies[i]->oneStep();
  }
  for (std::size_t i = 0; i < m_bodies.size(); i++)
  {
    m_bodies[i]->updateState();
  }
  for (std::size_t i = 0; i < m_masslessBodies.size(); i++)
  {
    m_masslessBodies[i]->oneStep();
  }
  for (std::size_t i = 0; i < m_masslessBodies.size(); i++)
  {
    m_masslessBodies[i]->updateState();
  }

}


std::array<double, 4>
Environment::getStateDerivative(const std::array<double, 4>& x)
{
  double r;
  double mass;
  double x12[2];

  stateDerivative[2] = 0.0;
  stateDerivative[3] = 0.0;

  for (auto iter = m_bodies.begin(); iter != m_bodies.end(); iter++)
  {
    x2 = (*iter)->getState();
    if (x2[0] != x[0] && x2[1] != x[1])
    {
      mass = (*iter)->getMass();
      x12[0] = x[0]-x2[0];
      x12[1] = x[1]-x2[1];
      r = sqrt(x12[0]*x12[0]+x12[1]*x12[1]);
      if (r > 10)
      {
        stateDerivative[2] -= (mass)/(r*r*r) * x12[0];
        stateDerivative[3] -= (mass)/(r*r*r) * x12[1];
      }
    }
  }

  stateDerivative[0] = x[2];
  stateDerivative[1] = x[3];

  return stateDerivative;
}


void
Environment::mergeBodies()
{
  double x12, y12, r12;
  bool localcol = false;
  double massNew, xNew, yNew, vxNew, vyNew;

  for (auto iter = m_bodies.begin(); iter != m_bodies.end();)
  {
    x1 = (*iter)->getState();
    para1 = (*iter)->getParameters();

    for (auto iter2 = m_bodies.begin(); iter2 != m_bodies.end();)
    {
      x2 = (*iter2)->getState();
      para2 = (*iter2)->getParameters();
      x12 = x2[0]-x1[0];
      y12 = x2[1]-x1[1];
      r12 = sqrt(x12*x12+y12*y12);

      if ( (iter2 != iter) && (r12 < (para1[1]+para2[1])) )
      {
        localcol = true;
        std::cout << "Collision" << std::endl;
        massNew = (para1[0]+para2[0]);
        xNew = (x1[0]*para1[0]+x2[0]*para2[0])/massNew;
        yNew = (x1[1]*para1[0]+x2[1]*para2[0])/massNew;
        vxNew = (para1[0]*x1[2]+para2[0]*x2[2]) / massNew;
        vyNew = (para1[0]*x1[3]+para2[0]*x2[3]) / massNew;

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
    x1 = (*iter)->getState();
    para1 = (*iter)->getParameters();

    for (auto iter2 = m_bodies.begin(); iter2 != m_bodies.end(); iter2++)
    {
      if (iter2 != iter)
      {
        x2 = (*iter2)->getState();
        para2 = (*iter2)->getParameters();
        x12 = x2[0]-x1[0];
        y12 = x2[1]-x1[1];
        r12 = sqrt(x12*x12+y12*y12);

        potentialEnergy -= para1[0]*para2[0]/r12;
      }
    }
    kineticEnergy += 0.5*para1[0]*(x1[2]*x1[2]+x1[3]*x1[3]);
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
    x1 = (*iter)->getState();
    para1 = (*iter)->getParameters();
    linearMomentum += para1[0]*x1[2];
  }

  return linearMomentum;
}
