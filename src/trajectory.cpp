#include "SDL_gfxPrimitives.h"

#include "trajectory.hpp"
#include "importsettings.hpp"

Trajectory::Trajectory(SDL_Surface* screen)
  : m_screen(screen),
    m_lineColorRate(import::getLineColorRate()),
    m_x(),
    m_y()
{
}


void
Trajectory::addPoint(double x, double y)
{
  m_x.push_back(x);
  m_y.push_back(y);
}


void
Trajectory::draw()
{
  std::cout << "Trajectory::draw() - m_x.size(): " << m_x.size() << std::endl;
  std::cout << "Trajectory::draw() - i < m_x.size()-1: " << (0 < m_x.size()-1) << std::endl;
  for (std::size_t i = 0; i < m_x.size()-1; ++i)
  {
    std::cout << "Trajectory::draw() - in loop" << std::endl;
    aalineRGBA(m_screen, m_x[i], m_y[i], m_x[i+1], m_y[i+1], (cos(i/m_lineColorRate)+1)*255/2.0, (sin(i/m_lineColorRate)+1)*255/2.0, 0, 255);
  }
}
