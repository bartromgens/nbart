/*
 * importsettings.hpp
 *
 *  Created on: Apr 24, 2010
 *      Author: annom
 */

#ifndef IMPORTSETTINGS_HPP_
#define IMPORTSETTINGS_HPP_

#include <stdlib.h>
#include <iostream>
#include <fstream>

namespace import {

  void importSettings(double* settings);
  int getFullscreen();
  int getHres();
  int getVres();
  int getFPS();
  int getNBodies();
  double getStepSize();
  double getSimulationSpeed();
  int getLineRate();
  double getLineColorRate();

}

#endif /* IMPORTSETTINGS_HPP_ */
