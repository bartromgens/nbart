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
//  std::cout << __PRETTY_FUNCTION__ << std::endl;
  m_x.push_back(x);
  m_y.push_back(y);
}


void
Trajectory::draw()
{
  if (m_x.size() < 2)
  {
    return;
  }

  for (std::size_t i = 0; i < m_x.size()-1; ++i)
  {
    int r = (cos(i/m_lineColorRate)+1)*255/2.0;
    int g = (sin(i/m_lineColorRate)+1)*255/2.0;
    int b = 0;
    int a = 255;
    aalineRGBA(m_screen, m_x[i], m_y[i], m_x[i+1], m_y[i+1], r, g, b, a);
    aalineRGBA(m_screen, m_x[i]+1, m_y[i], m_x[i+1]+1, m_y[i+1], r, g, b, a);
    aalineRGBA(m_screen, m_x[i]-1, m_y[i], m_x[i+1]-1, m_y[i+1], r, g, b, a);
  }
}
