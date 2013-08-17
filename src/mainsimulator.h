#ifndef MAINSIMULATOR_H
#define MAINSIMULATOR_H

#include <SDL/SDL.h>
#include <memory>

class SimulatorController;
class Environment;

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

  void handleKeyAndMouseEvents(Environment* environment, SDL_Surface* screen, MouseState& mouseState);

  void handleKeyEvent(SDL_Event event, Environment* environment, SDL_Surface* screen);

  void handleMouseEvent(SDL_Event event, Environment* environment, SDL_Surface* screen, MouseState& mouseState);
private:
  std::shared_ptr<SimulatorController> m_controller;
};

#endif // MAINSIMULATOR_H
