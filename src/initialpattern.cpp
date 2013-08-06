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
std::vector<Body* >
initialpattern::createPattern1(std::vector<Body* > bodyvec, Environment* environment, SDL_Surface* screen, int nBodies, double mass)
{
  const int SCREEN_WIDTH = import::getHres();
  const int SCREEN_HEIGHT = import::getVres();

  for (int i = 0; i < nBodies; i++)
  {
    Body* body = new Body(environment, screen, "./data/blurball.png");
    environment->addBody(body);
    bodyvec.push_back(body);
    bodyvec.back()->setMass( mass );
    bodyvec.back()->setRadius(sqrt(mass*20));
    int r = 300;
    double theta = i*360.0/nBodies/180.0*M_PI;
    bodyvec.back()->setPosition(SCREEN_WIDTH/2.0+r*cos(theta), SCREEN_HEIGHT/2.0+r*sin(theta));
    bodyvec.back()->setVelocity(-0.1*sin(theta),0.1*cos(theta));
    //bodyvec.back()->setVelocity(0.3*sin(theta),0.3*cos(theta));
    //        bodyvec.back()->setVelocity(0,0);
  }
  return bodyvec;
}

// Random pattern
std::vector<Body* >
initialpattern::createPattern2(std::vector<Body* > bodyvec, Environment* environment, SDL_Surface* screen, int nBodies)
{
  const int SCREEN_WIDTH = import::getHres();
  const int SCREEN_HEIGHT = import::getVres();

  for (int i = 0; i < nBodies; i++)
  {
    Body* body = new Body(environment, screen, "./data/whiteball.png");
    environment->addBody(body);
    bodyvec.push_back(body);
    double mass = random(0.01, 0.1);
    bodyvec.back()->setMass( mass );
    bodyvec.back()->setRadius(2);
    bodyvec.back()->setPosition(random(0, SCREEN_WIDTH), random(0, SCREEN_HEIGHT));
    bodyvec.back()->setVelocity(random(-0.01,0.01), random(-0.01,0.01));
  }
  return bodyvec;
}

// Spiral Pattern
std::vector<Body* >
initialpattern::createPattern3(std::vector<Body* > bodyvec, Environment* environment, SDL_Surface* screen, int nBodies)
{
  const int SCREEN_WIDTH = import::getHres();
  const int SCREEN_HEIGHT = import::getVres();

  for (int i = 0; i < nBodies; i++)
  {
    Body* body = new Body(environment, screen, "./data/whiteball.png");
    environment->addBody(body);
    bodyvec.push_back(body);
    double mass = random(50/nBodies, 50/nBodies);
    bodyvec.back()->setMass( mass );
    bodyvec.back()->setRadius(sqrt(mass*10));
    //bodyvec.back()->setPosition(random(0, SCREEN_WIDTH), random(0, SCREEN_HEIGHT));
    //bodyvec.back()->setVelocity(random(-0.2,0.2), random(-0.2,0.2));
    int r = SCREEN_WIDTH/nBodies/3.0*(i+1);
    double theta = i*360.0/nBodies/180.0*M_PI;
    bodyvec.back()->setPosition(SCREEN_WIDTH/2.0+r*cos(theta), SCREEN_HEIGHT/2.0+r*sin(theta));
    bodyvec.back()->setVelocity(-sqrt(mass/r)*sin(theta),sqrt(mass/r)*cos(theta));
    //        bodyvec.back()->setVelocity(0.3*sin(theta),0.3*cos(theta));
    //        bodyvec.back()->setVelocity(0,0);
  }
  return bodyvec;
}

// Strange numero uno
std::vector<Body* >
initialpattern::createPattern4(std::vector<Body* > bodyvec, Environment* environment, SDL_Surface* screen, int nBodies)
{
  const int SCREEN_WIDTH = import::getHres();
  const int SCREEN_HEIGHT = import::getVres();

  for (int i = 0; i < nBodies; i++) {
    Body* body = new Body(environment, screen, "./data/whiteball.png");
    environment->addBody(body);
    bodyvec.push_back(body);
    double mass = random(3, 3);
    bodyvec.back()->setMass( mass );
    bodyvec.back()->setRadius(sqrt(mass*10));
    double theta = i*360.0/nBodies/180.0*M_PI;
    int r = 300;
    bodyvec.back()->setPosition(SCREEN_WIDTH/2.0+r*cos(theta), SCREEN_HEIGHT/2.0+r*sin(theta));
    bodyvec.back()->setVelocity(0.2*sin(theta),0.2*cos(theta));
    //        bodyvec.back()->setVelocity(0.3*sin(theta),0.3*cos(theta));
  }
  return bodyvec;
}

// Strange numero uno
std::vector<Body* >
initialpattern::createPattern5(std::vector<Body* > bodyvec, Environment* environment, SDL_Surface* screen, int nBodies)
{
  const int SCREEN_WIDTH = import::getHres();
  const int SCREEN_HEIGHT = import::getVres();

  for (int i = 0; i < nBodies; i++)
  {
    Body* body = new Body(environment, screen, "./data/whiteball.png");
    environment->addBody(body);
    bodyvec.push_back(body);

    double mass = random(1, 10);
    bodyvec.back()->setMass( mass );
    bodyvec.back()->setRadius(sqrt(mass*10));
    double theta = i*360.0/nBodies/180.0*M_PI;
    int r = 300;
    bodyvec.back()->setPosition(i*SCREEN_WIDTH/nBodies, SCREEN_HEIGHT/2.0+r*sin(theta));
    bodyvec.back()->setVelocity(0.2*sin(theta),0.2*cos(theta));
    //        bodyvec.back()->setVelocity(0.3*sin(theta),0.3*cos(theta));
  }
  return bodyvec;
}
