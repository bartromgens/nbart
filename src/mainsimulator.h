#ifndef MAINSIMULATOR_H
#define MAINSIMULATOR_H

#include <SDL/SDL.h>
#include <memory>
#include <vector>

class SimulatorController;
class Environment;
class Body;

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

  void handleKeyAndMouseEvents(std::vector<Environment*> environments, SDL_Surface* screen, MouseState& mouseState);

  void handleKeyEvent(SDL_Event event, std::vector<Environment*> environments, SDL_Surface* screen);

  void handleMouseEvent(SDL_Event event, std::vector<Environment*> environments, SDL_Surface* screen, MouseState& mouseState);

  static void sortBodies(std::vector<Body*> bodies);

private:
  std::shared_ptr<SimulatorController> m_controller;

  static int nEnvironments;

  int m_screenWidth;
  int m_screenHeight;
  int m_fps;
};

#endif // MAINSIMULATOR_H
