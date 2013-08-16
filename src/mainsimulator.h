#ifndef MAINSIMULATOR_H
#define MAINSIMULATOR_H

#include <memory>

class SimulatorController;
class Environment;
class SDL_Surface;

class MainSimulator
{
public:
  MainSimulator(std::shared_ptr<SimulatorController> controller);
  ~MainSimulator();

  void run();

  void handleKeyAndMouseEvents(Environment* environment,
                               SDL_Surface* screen,
                               int &mousedownX,
                               int &mousedownY,
                               int &mouseupX,
                               int &mouseupY);
private:
  std::shared_ptr<SimulatorController> m_controller;
};

#endif // MAINSIMULATOR_H
