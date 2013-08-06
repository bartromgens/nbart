#ifndef INITIALPATTERN_H
#define INITIALPATTERN_H

#include <iostream>
#include <vector>

class Body;
class Environment;
class SDL_Surface;

namespace initialpattern
{

int factorial(int number);

double random(double start, double end);

std::vector<Body*> createPattern1(std::vector<Body* > bodyvec, Environment* environment, SDL_Surface* screen, int nBodies, double mass);
std::vector<Body*> createPattern2(std::vector<Body* > bodyvec, Environment* environment, SDL_Surface* screen, int nBodies);
std::vector<Body*> createPattern3(std::vector<Body* > bodyvec, Environment* environment, SDL_Surface* screen, int nBodies);
std::vector<Body*> createPattern4(std::vector<Body* > bodyvec, Environment* environment, SDL_Surface* screen, int nBodies);
std::vector<Body*> createPattern5(std::vector<Body* > bodyvec, Environment* environment, SDL_Surface* screen, int nBodies);

}

#endif // INITIALPATTERN_H
