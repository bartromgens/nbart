#include "gravityfield.hpp"

#include "node.hpp"
#include "environment.hpp"

GravityField::GravityField(int nVerticalTiles, int nHorizontalTiles, int tileSize, int tileBorderSize)
  : m_field(nVerticalTiles, std::vector<Node*>(nHorizontalTiles)),
    m_outtiles(nVerticalTiles, std::vector<SDL_Rect>(nHorizontalTiles)),
    m_insidetiles(nVerticalTiles, std::vector<SDL_Rect>(nHorizontalTiles)),
    m_nVerticalTiles(nVerticalTiles),
    m_nHorizontalTiles(nHorizontalTiles),
    m_tileSize(tileSize),
    m_tileBorderSize(tileBorderSize)
{  
  std::cout << "GravityField::GravityField()" << std::endl;

  for (int i = 0; i < m_nVerticalTiles; i++)
  {
    for (int j = 0; j < m_nHorizontalTiles; j++)
    {
      m_field[i][j] = new Node(j,i);
    }
  }

  setTilePositions();
}


GravityField::~GravityField()
{
  std::cout << "GravityField::~GravityField()" << std::endl;

  for (int i = 0; i < m_nVerticalTiles; i++)
  {
    for (int j = 0; j < m_nHorizontalTiles; j++)
    {
      delete m_field[i][j];
    }
  }
}


void
GravityField::draw(SDL_Surface* screen, Environment* environment)
{
  for (int i = 0; i < m_nVerticalTiles; i++)
  {
    for (int j = 0; j < m_nHorizontalTiles; j++)
    {
      SDL_FillRect( screen, &m_outtiles[i][j], SDL_MapRGB( screen->format, 0, 0, 0) );

      double fieldStrength = environment->getFieldStrength(j*m_tileSize+m_tileSize/2.0,i*m_tileSize+m_tileSize/2.0) * 3.0e7;

      fieldStrength = pow(fieldStrength, 1.0/3.0);

      if (fieldStrength > 255)
      {
        fieldStrength = 255;
      }

      SDL_FillRect( screen, &m_insidetiles[i][j], SDL_MapRGB( screen->format, fieldStrength, 0, 0) );
    }
  }
}


void
GravityField::setTilePositions()
{
  for (int i = 0; i < m_nVerticalTiles; i++)
  {
    for (int j = 0; j < m_nHorizontalTiles; j++)
    {
      m_outtiles[i][j].x = m_tileSize*j;
      m_outtiles[i][j].y = m_tileSize*i;
      m_outtiles[i][j].w = m_tileSize;
      m_outtiles[i][j].h = m_tileSize;
    }
  }

  for (int i = 0; i < m_nVerticalTiles; i++)
  {
    for (int j = 0; j < m_nHorizontalTiles; j++)
    {
      m_insidetiles[i][j].x = (m_tileSize*j)-m_tileBorderSize;
      m_insidetiles[i][j].y = (m_tileSize*i)-m_tileBorderSize;
      m_insidetiles[i][j].w = m_tileSize-(2*m_tileBorderSize);
      m_insidetiles[i][j].h = m_tileSize-(2*m_tileBorderSize);
    }
  }
}
