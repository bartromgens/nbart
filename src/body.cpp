#include "drawable.hpp"
#include "drawableBody.hpp"
#include "integrator.hpp"
#include "environment.hpp"
#include "importsettings.hpp"

#include "body.hpp"

Body::Body(Environment* environment, SDL_Surface *screen, std::string imageloc) {
    drawbody = new DrawableBody(screen, imageloc);
    trajectory = new Trajectory(screen);
    this->environment = environment;
    nStep = 0;
    dimx = 4;
    dimpar = 2;
    stepsize = import::getStepSize();
    linerate = import::getLineRate();
    x = new double[dimx];
    xNew = new double[dimx];
    para = new double[dimpar];
    x[0] = 200.0;
    x[1] = 200.0;
    x[2] = 0;
    x[3] = 0;
        
    para[0] = .1e1; // mass [kg]
    para[1] = 15.0; // radius [m]
    drawbody->setSize(2*para[1]);
    integrator = new Integrator(environment, x, para, dimx, dimpar, stepsize);
    setScreenCenterPos((int)x[0],(int)x[1]);
};

Body::~Body() {
};

void Body::draw() {
    drawbody->draw();
};

void Body::drawTrajectory() {
    trajectory->draw();
};

void Body::oneStep() {
    xNew = integrator->integrate(1);
};

void Body::updateState() {
    for (int i = 0; i < dimx; i++) {
        x[i] = xNew[i];
    }
    
    if (nStep%(10*linerate) == 0) {
        trajectory->addPoint(x[0],x[1]);
    }
    setScreenCenterPos((int)x[0],(int)x[1]);
    nStep++;
};
    
void Body::setPosition(double xin, double yin) {
    this->x[0] = xin;
    this->x[1] = yin;
    integrator = new Integrator(environment, x, para, dimx, dimpar, stepsize);
    setScreenCenterPos((int)x[0],(int)x[1]);
};

void Body::setVelocity(double vxin, double vyin) {
    this->x[2] = vxin;
    this->x[3] = vyin;
    integrator = new Integrator(environment, x, para, dimx, dimpar, stepsize);
};

void Body::setScreenCenterPos(int x, int y) {
    drawbody->setCenterPos(x,y);
};
	
void Body::moveScreenCenterPos(int dx, int dy) {
    drawbody->moveCenterPos(dx, dy); 
};

void Body::setMass(double mass) {
    this->para[0] = mass;
    integrator = new Integrator(environment, x, para, dimx, dimpar, stepsize);
};

void Body::setRadius(double radius) {
    this->para[1] = radius;
    drawbody->setSize(2*para[1]);
    integrator = new Integrator(environment, x, para, dimx, dimpar, stepsize);
};


double Body::getMass() {
    return para[0];
};

double* Body::getState() {
    return x;
};

double* Body::getParameters() {
    return para;
};

double Body::random(double start, double end) {
    double randomDouble = start+(end-start)*rand()/(RAND_MAX + 1.0);
    return randomDouble;
};

