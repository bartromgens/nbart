#ifndef TRAJECTORY_H_
#define TRAJECTORY_H_

#include <iostream>
#include "SDL/SDL.h"



class Trajectory {
private:
	SDL_Surface *screen;
	int entries;
	double x[100000];
	double y[100000];

public:
	Trajectory(SDL_Surface* screen);
    double lineColorRate;

	void addPoint(double x, double y);
	void draw();
};

#endif /* TRAJECTORY_H_ */
