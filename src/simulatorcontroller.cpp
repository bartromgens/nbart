#include "simulatorcontroller.h"

#include <iostream>

SimulatorController::SimulatorController()
  : m_close(false),
    m_clear(false)
{
}


SimulatorController::~SimulatorController()
{
  std::cout << "~SimulatorController::SimulatorController()" << std::endl;
}


void
SimulatorController::setClose(bool close)
{
  m_close = close;
}


bool
SimulatorController::getClose()
{
  return m_close;
}


void
SimulatorController::setClear(bool clear)
{
  m_clear = clear;
}


bool
SimulatorController::getClear() const
{
  return m_clear;
}
