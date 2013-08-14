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

void createPattern1(Environment* environment, SDL_Surface* screen, int nBodies, double mass);
void createPattern2(Environment* environment, SDL_Surface* screen, int nBodies);
void createPattern3(Environment* environment, SDL_Surface* screen, int nBodies);
void createPattern4(Environment* environment, SDL_Surface* screen, int nBodies);
void createPattern5(Environment* environment, SDL_Surface* screen, int nBodies);

}

#endif // INITIALPATTERN_H
