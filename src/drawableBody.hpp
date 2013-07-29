#ifndef DRAWABLEBODY_H_
#define DRAWABLEBODY_H_

#include "drawable.hpp"

//!  RK4 (Runge Kutta 4th order) fixed stepsize integrator class
/*!
   The most basic and conventional higher order RK4 ODE integrator.
   A RK4 object is composed of a EOMrk equations of motion object. 
   A pointer to this EOMrk object is passed as parameter. 
*/
class DrawableBody : public Drawable {
public:
    DrawableBody(SDL_Surface *screen, std::string imageloc);
    
protected:

private:

};

#endif /* DRAWABLEBODY_H_ */
