#include "initialpattern.hpp"

#include "body.hpp"
#include "importsettings.hpp"
#include "environment.hpp"

#include <cmath>

int
initialpattern::factorial(int i)
{
  if (i <= 1)
    return i;
  return (i * factorial(i - 1));
}


double
initialpattern::random(double start, double end)
{
  double randomDouble = start+(end-start)*rand()/(RAND_MAX + 1.0);
  return randomDouble;
}


// Orbiting Pattern
void
initialpattern::createPattern1(Environment* environment, int nBodies, double mass)
{
  const int SCREEN_WIDTH = import::getHres();
  const int SCREEN_HEIGHT = import::getVres();

  for (int i = 0; i < nBodies; i++)
  {
    Body* body = new Body("./data/blurball.png");
    environment->addBody(body);
    body->setMass( mass );
    body->setRadius(sqrt(mass*20));
    int r = 300;
    double theta = i*360.0/nBodies/180.0*M_PI;
    body->setPosition(SCREEN_WIDTH/2.0+r*cos(theta), SCREEN_HEIGHT/2.0+r*sin(theta));
    body->setVelocity(-0.1*sin(theta),0.1*cos(theta));
  }
}

// Random pattern
void
initialpattern::createPattern2(Environment* environment, int nBodies)
{
  const int SCREEN_WIDTH = import::getHres();
  const int SCREEN_HEIGHT = import::getVres();

  for (int i = 0; i < nBodies; i++)
  {
    Body* body = new Body("./data/whiteball.png");
    environment->addBody(body);
    double mass = random(0.01, 0.1);
    body->setMass( mass );
    body->setRadius(2);
    body->setPosition(random(0, SCREEN_WIDTH), random(0, SCREEN_HEIGHT));
    body->setVelocity(random(-0.01,0.01), random(-0.01,0.01));
  }
}

// Spiral Pattern
void
initialpattern::createPattern3(Environment* environment, int nBodies)
{
  const int SCREEN_WIDTH = import::getHres();
  const int SCREEN_HEIGHT = import::getVres();

  for (int i = 0; i < nBodies; i++)
  {
    Body* body = new Body("./data/whiteball.png");
    environment->addBody(body);
    double mass = random(50/nBodies, 50/nBodies);
    body->setMass( mass );
    body->setRadius(sqrt(mass*10));
    //body->setPosition(random(0, SCREEN_WIDTH), random(0, SCREEN_HEIGHT));
    //body->setVelocity(random(-0.2,0.2), random(-0.2,0.2));
    int r = SCREEN_WIDTH/nBodies/3.0*(i+1);
    double theta = i*360.0/nBodies/180.0*M_PI;
    body->setPosition(SCREEN_WIDTH/2.0+r*cos(theta), SCREEN_HEIGHT/2.0+r*sin(theta));
    body->setVelocity(-sqrt(mass/r)*sin(theta),sqrt(mass/r)*cos(theta));
    //        body->setVelocity(0.3*sin(theta),0.3*cos(theta));
    //        body->setVelocity(0,0);
  }
}

// Strange numero uno
void
initialpattern::createPattern4(Environment* environment, int nBodies)
{
  const int SCREEN_WIDTH = import::getHres();
  const int SCREEN_HEIGHT = import::getVres();

  for (int i = 0; i < nBodies; i++) {
    Body* body = new Body("./data/whiteball.png");
    environment->addBody(body);
    double mass = random(3, 3);
    body->setMass( mass );
    body->setRadius(sqrt(mass*10));
    double theta = i*360.0/nBodies/180.0*M_PI;
    int r = 300;
    body->setPosition(SCREEN_WIDTH/2.0+r*cos(theta), SCREEN_HEIGHT/2.0+r*sin(theta));
    body->setVelocity(0.2*sin(theta),0.2*cos(theta));
    //        body->setVelocity(0.3*sin(theta),0.3*cos(theta));
  }
}

// Strange numero uno
void
initialpattern::createPattern5(Environment* environment, int nBodies)
{
  const int SCREEN_WIDTH = import::getHres();
  const int SCREEN_HEIGHT = import::getVres();

  for (int i = 0; i < nBodies; i++)
  {
    Body* body = new Body("./data/whiteball.png");
    environment->addBody(body);

    double mass = random(1, 10);
    body->setMass( mass );
    body->setRadius(sqrt(mass*10));
    double theta = i*360.0/nBodies/180.0*M_PI;
    int r = 300;
    body->setPosition(i*SCREEN_WIDTH/nBodies, SCREEN_HEIGHT/2.0+r*sin(theta));
    body->setVelocity(0.2*sin(theta),0.2*cos(theta));
    //        body->setVelocity(0.3*sin(theta),0.3*cos(theta));
  }
}
