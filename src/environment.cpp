#include <cmath>

#include "importsettings.hpp"

#include "environment.hpp"

Environment::Environment(SDL_Surface* screen) {
  this->screen = screen;
  stateDerivative = new double[4];
  hres = import::getHres();
  vres = import::getVres();
  nBodies = import::getNBodies();
}

Environment::~Environment() {
}

void Environment::addBody(Body* body) {
  bodyvec.push_back(body);
}

void Environment::addMasslessBody(Body* body) {
  masslessbodyvec.push_back(body);
}

void Environment::clearAllBodies() {
  bodyvec.clear();
  masslessbodyvec.clear();
}

void Environment::drawBodies() {
  for (std::size_t i = 0; i < bodyvec.size(); i++) {
    bodyvec[i]->draw();
  }
  for (std::size_t i = 0; i < masslessbodyvec.size(); i++) {
    masslessbodyvec[i]->draw();
  }
}

void Environment::drawTrajectories() {
  for (std::size_t i = 0; i < bodyvec.size(); i++) {
    bodyvec[i]->drawTrajectory();
  }
}

void Environment::oneStep() {
  for (std::size_t i = 0; i < bodyvec.size(); i++) {
    bodyvec[i]->oneStep();
  }
  for (std::size_t i = 0; i < bodyvec.size(); i++) {
    bodyvec[i]->updateState();
  }
  for (std::size_t i = 0; i < masslessbodyvec.size(); i++) {
    masslessbodyvec[i]->oneStep();
  }
  for (std::size_t i = 0; i < masslessbodyvec.size(); i++) {
    masslessbodyvec[i]->updateState();
  }

}

double* Environment::getStateDerivative(double* x, double* para) {
  double* x2;
  double r;
  double mass;
  double x12[2];
  stateDerivative[2] = 0.0;
  stateDerivative[3] = 0.0;

  for (bodyit = bodyvec.begin(); bodyit != bodyvec.end(); bodyit++) {
    x2 = (*bodyit)->getState();
    if (x2[0] != x[0] && x2[1] != x[1]) {
      mass = (*bodyit)->getMass();
      x12[0] = x[0]-x2[0];
      x12[1] = x[1]-x2[1];
      r = sqrt(x12[0]*x12[0]+x12[1]*x12[1]);
      if (r > 10) {
        stateDerivative[2] -= (mass)/(r*r*r) * x12[0];
        stateDerivative[3] -= (mass)/(r*r*r) * x12[1];
      }
    }
  }

  stateDerivative[0] = x[2];
  stateDerivative[1] = x[3];

  // Walls
  //    if (x[0] < 0) {
  //        x[2] = x[2]*-1;
  //        x[0] += 8;
  //    } else if (x[0] > hres) {
  //        x[2] = x[2]*-1;
  //        x[0] -= 8;
  //    } else if (x[1] < 0) {
  //        x[3] = x[3]*-1;
  //        x[1] += 8;
  //    } else if (x[1] > vres) {
  //        x[3] = x[3]*-1;
  //        x[1] -= 8;
  //    }
  return stateDerivative;
}

void Environment::mergeBodies() {
  std::vector<Body* >::iterator bodyit2;

  double* x1;
  double* x2;
  double* para1;
  double* para2;
  double x12, y12, r12;
  bool localcol = false;
  double massNew, xNew, yNew, vxNew, vyNew;

  for (bodyit = bodyvec.begin(); bodyit != bodyvec.end();) {
    x1 = (*bodyit)->getState();
    para1 = (*bodyit)->getParameters();

    for (bodyit2 = bodyvec.begin(); bodyit2 != bodyvec.end();) {
      x2 = (*bodyit2)->getState();
      para2 = (*bodyit2)->getParameters();
      x12 = x2[0]-x1[0];
      y12 = x2[1]-x1[1];
      r12 = sqrt(x12*x12+y12*y12);

      if ( (bodyit2 != bodyit) && (r12 < (para1[1]+para2[1])) )  {
        localcol = true;
        std::cout << "Collision" << std::endl;
        massNew = (para1[0]+para2[0]);
        xNew = (x1[0]*para1[0]+x2[0]*para2[0])/massNew;
        yNew = (x1[1]*para1[0]+x2[1]*para2[0])/massNew;
        vxNew = (para1[0]*x1[2]+para2[0]*x2[2]) / massNew;
        vyNew = (para1[0]*x1[3]+para2[0]*x2[3]) / massNew;

        
        bodyit2 = bodyvec.erase(bodyit2);
        break;
      } else {
        bodyit2++;
      }
    }

    if (localcol) {
      bodyit = bodyvec.erase(bodyit);
      break;
    } else {
      bodyit++;
    }
  }

  if (localcol) {
    Body* body = new Body(this, screen, "./data/blurball.png");
    body->setMass(massNew);
    body->setRadius(sqrt(massNew*20));
    body->setPosition(xNew, yNew);
    body->setVelocity(vxNew, vyNew);
    addBody(body);
    localcol = false;
  }
}

double Environment::getFieldStrength(double x, double y) {
  double* x2;
  double r;
  double mass;
  double x12[2];
  double gravityForce = 0.0;
  double gravityForceX = 0.0;
  double gravityForceY = 0.0;

  for (bodyit = bodyvec.begin(); bodyit != bodyvec.end(); bodyit++) {
    x2 = (*bodyit)->getState();
    if (x2[0] != x && x2[1] != y) {
      mass = (*bodyit)->getMass();
      x12[0] = x-x2[0];
      x12[1] = y-x2[1];
      r = sqrt(x12[0]*x12[0]+x12[1]*x12[1]);
      if (r > 1) {
        gravityForceX += mass/(r*r*r)*x12[0];
        gravityForceY += mass/(r*r*r)*x12[1];
      }
    }
  }

  gravityForce = sqrt(pow(gravityForceX,2)+pow(gravityForceY,2));
  return gravityForce;
}

double Environment::getEnergy() {
  double energy;
  double kineticEnergy = 0.0;
  double potentialEnergy = 0.0;
  double* x1;
  double* para1;
  double* x2;
  double* para2;
  double x12, y12, r12;

  std::vector<Body* >::iterator bodyit2;

  for (bodyit = bodyvec.begin(); bodyit != bodyvec.end(); bodyit++) {
    x1 = (*bodyit)->getState();
    para1 = (*bodyit)->getParameters();

    for (bodyit2 = bodyvec.begin(); bodyit2 != bodyvec.end(); bodyit2++) {
      if (bodyit2 != bodyit) {
        x2 = (*bodyit2)->getState();
        para2 = (*bodyit2)->getParameters();
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

double Environment::getLinearMomentum() {
  double linearMomentum = 0;
  double* x;
  double* para;

  for (bodyit = bodyvec.begin(); bodyit != bodyvec.end(); bodyit++) {
    x = (*bodyit)->getState();
    para = (*bodyit)->getParameters();
    linearMomentum += para[0]*x[2];
  }

  return linearMomentum;
}
