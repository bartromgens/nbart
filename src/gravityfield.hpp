#ifndef GRAVITYFIELD_H
#define GRAVITYFIELD_H

#include "SDL/SDL.h"

#include <iostream>
#include <vector>

class Environment;
class Node;
class SDL_Surface;

class GravityField
{
public:
  GravityField(int nVerticalTiles, int nHorizontalTiles, int tileSize, int tileBorderSize);
  ~GravityField();

  void draw(SDL_Surface *screen, Environment* environment);

private:
  void setTilePositions();

private:
  std::vector<std::vector<Node*> > m_field;
  std::vector<std::vector<SDL_Rect> > m_outtiles;
  std::vector<std::vector<SDL_Rect> > m_insidetiles;

  int m_nVerticalTiles;
  int m_nHorizontalTiles;
  int m_tileSize;
  int m_tileBorderSize;
};

#endif // GRAVITYFIELD_H
