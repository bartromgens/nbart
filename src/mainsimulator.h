#ifndef MAINSIMULATOR_H
#define MAINSIMULATOR_H

#include <SDL/SDL.h>

#include <map>
#include <list>
#include <memory>
#include <vector>

class Drawable;
class Body;
class Environment;
class SimulatorController;
class Trajectory;

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

private:
  Body* createBody(Environment* environment, int mass, SDL_Surface* screen, std::string imageloc);
  Body* createMasslessBody(Environment* environment, SDL_Surface* screen, std::string imageloc);

//  void filterBodiesByDistance(int distance_px);
  void sortBodies(std::map<std::size_t, const Body*> bodies, std::vector<Environment*> environments);
  void deleteAllBodies(std::vector<Environment*> environments);
  void oneStep(std::vector<Environment*> environments);
  void drawBodies();
  void updateBodyList(std::vector<Environment*> environments);

private:
  std::shared_ptr<SimulatorController> m_controller;

  static int nEnvironments;

  std::map<std::size_t, const Body*> m_bodies;
  std::map<std::size_t, std::unique_ptr<Drawable>> m_drawableBodies;
  std::map<std::size_t, std::unique_ptr<Trajectory>> m_trajectories;

  double m_massUserDefined;

  int m_screenWidth;
  int m_screenHeight;
  int m_fps;

};

#endif // MAINSIMULATOR_H
