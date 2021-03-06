#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#include "importsettings.hpp"

#include <QFile>

#include <cassert>

void
import::importSettings(double* settings)
{
  std::string filename = "settings.txt";
  if ( !QFile::exists(QString::fromStdString(filename)) )
  {
    std::cout << "Import settings failed, file " << filename << " does not exist!" << std::endl;
    assert(false); // we cannot continue without a settings file at the moment
  }

  std::string line;
  std::ifstream infile(filename);
  for (int i = 0; i < 9; i++)
  {
    getline(infile, line);
    getline(infile, line);
    settings[i] = atof(line.c_str());
  }
}


int
import::getFullscreen()
{
  double settings[10];
  importSettings(settings);
  return (int)settings[0];
}


int
import::getHres()
{
  double settings[10];
  importSettings(settings);
  if (settings[1] == 0)
  {
    SDL_Init( SDL_INIT_EVERYTHING );
    const SDL_VideoInfo* vidinfo = SDL_GetVideoInfo();
    settings[1] = vidinfo->current_w;
  }
  return settings[1];
}


int
import::getVres()
{
  double settings[10];
  importSettings(settings);
  if (settings[1] == 0)
  {
    SDL_Init( SDL_INIT_EVERYTHING );
    const SDL_VideoInfo* vidinfo = SDL_GetVideoInfo();
    settings[2] = vidinfo->current_h;
  }
  return settings[2];
}


int
import::getFPS()
{
  double settings[10];
  importSettings(settings);
  return (int)settings[3];
}


int
import::getNBodies()
{
  double settings[10];
  importSettings(settings);
  return (int)settings[4];
}


double
import::getStepSize()
{
  double settings[10];
  importSettings(settings);
  return settings[5];
}


double
import::getSimulationSpeed()
{
  double settings[10];
  importSettings(settings);
  return settings[6];
}


int
import::getLineRate()
{
  double settings[10];
  importSettings(settings);
  return (int)settings[7];
}


double
import::getLineColorRate()
{
  double settings[10];
  importSettings(settings);
  return settings[8];
}
