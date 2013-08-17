#ifndef MAINSIMULATOR_H
#define MAINSIMULATOR_H

#include <memory>

class SimulatorController;
class Environment;
class SDL_Surface;

struct MouseState
{
  int m_mousedownX;
  int m_mousedownY;
  int m_mouseupX;
  int m_mouseupY;
};

class MainSimulator
{
public:
  MainSimulator(std::shared_ptr<SimulatorController> controller);
  ~MainSimulator();

  void run();

  void handleKeyAndMouseEvents(Environment* environment,
                               SDL_Surface* screen,
                               MouseState& mouseState);
private:
  std::shared_ptr<SimulatorController> m_controller;
};

#endif // MAINSIMULATOR_H
