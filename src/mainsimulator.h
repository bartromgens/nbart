#ifndef MAINSIMULATOR_H
#define MAINSIMULATOR_H

#include <memory>

class SimulatorController;

class MainSimulator
{
public:
  MainSimulator(std::shared_ptr<SimulatorController> controller);
  ~MainSimulator();

  void run();

private:
  std::shared_ptr<SimulatorController> m_controller;
};

#endif // MAINSIMULATOR_H
