#include "simulatorcontroller.h"

#include <iostream>

SimulatorController::SimulatorController()
  : m_close(false),
    m_clear(false),
    m_play(true),
    m_showBodies(true),
    m_showTrajectories(false),
    m_showField(false),
    m_simulationSpeed(10.0),
    m_stepsize(0.005)
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
SimulatorController::getClose() const
{
  return m_close;
}


bool
SimulatorController::getClear() const
{
  return m_clear;
}


void
SimulatorController::setClear(bool clear)
{
  m_clear = clear;
}


void
SimulatorController::togglePlay()
{
  m_play = !m_play;
}


bool
SimulatorController::getPlay() const
{
  return m_play;
}


bool
SimulatorController::getShowTrajectories() const
{
  return m_showTrajectories;
}


void
SimulatorController::setShowTrajectories(bool showTrajectories)
{
  m_showTrajectories = showTrajectories;
}


void
SimulatorController::toggleShowTrajectories()
{
  m_showTrajectories = !m_showTrajectories;
}


bool
SimulatorController::getShowField() const
{
  return m_showField;
}


void
SimulatorController::setShowField(bool showField)
{
  m_showField = showField;
}


void
SimulatorController::toggleShowField()
{
  m_showField = !m_showField;
}


double
SimulatorController::getSimulationSpeed() const
{
  return m_simulationSpeed;
}


void
SimulatorController::setSimulationSpeed(double simulationSpeed)
{
  m_simulationSpeed = simulationSpeed;
}


void
SimulatorController::increaseSimulationSpeed()
{
  m_simulationSpeed = m_simulationSpeed * 1.1;
}


void
SimulatorController::decreaseSimulationSpeed()
{
  m_simulationSpeed = m_simulationSpeed / 1.1;
}


bool
SimulatorController::getShowBodies() const
{
  return m_showBodies;
}


void SimulatorController::setShowBodies(bool showBodies)
{
  m_showBodies = showBodies;
}


void
SimulatorController::toggleShowBodies()
{
  m_showBodies = !m_showBodies;
}


void
SimulatorController::setStepSize(double stepsize)
{
  m_stepsize = stepsize;
}


double
SimulatorController::getStepSize() const
{
  return m_stepsize;
}
