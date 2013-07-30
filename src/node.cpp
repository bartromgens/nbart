#include "node.hpp"


Node::Node(int x, int y)
{
  this->x = x;
  this->y = y;
  wall = false;
  path = false;
  closed = false;
  opened = false;
  start = false;
  target = false;
  f = 10000.0;
  g = 10000.0;
  h = 20000.0;

  updateColor();
}


int
Node::getX()
{
  return x;
}


Color
Node::getColor()
{
  return color;
}


void Node::changeWall()
{
  wall = !wall;
  updateColor();
}


void Node::setWall(bool yesno)
{
  wall = yesno;
  updateColor();
}


void
Node::setPath(bool yesno)
{
  path = yesno;
  updateColor();
}


void
Node::setOpen(bool yesno)
{
  opened = yesno;
}


bool
Node::getOpen()
{
  return opened;
}


void
Node::setClose(bool yesno) {
  closed = yesno;
  if (yesno) {
    opened = false;
  }
  updateColor();
}


bool
Node::getClose()
{
  return closed;
}



void
Node::setStart(bool yesno)
{
  start = yesno;
  updateColor();
}


void
Node::setTarget(bool yesno)
{
  target = yesno;
  updateColor();
}


void
Node::updateColor()
{
  if (wall==true)
  {
    color.r = 80;
    color.g = 80;
    color.b = 255;
  }
  else if (target==true)
  {
    color.r = 255;
    color.g = 255;
    color.b = 255;
  }
  else if (start==true)
  {
    color.r = 0;
    color.g = 0;
    color.b = 0;
  }
  else if (closed==true)
  {
    color.r = 255;
    color.g = 255;
    color.b = 255;
  }
  else
  {
    color.r = 25;
    color.g = 100;
    color.b = 25;
  }

  if (path==true) {
    color.r = 255;
    color.g = 0;
    color.b = 0;
  }
}


void
Node::tryToOpen() {
  if ( wall==false && closed == false)
  {
    opened = true;
  };
}


void
Node::setParent(int x, int y)
{
  parent.x = x;
  parent.y = y;
}


Coordinate
Node::getParent()
{
  return parent;
}


void
Node::calcFGH(Coordinate start, Coordinate end, std::vector<std::vector<Node*> > field)
{
  f = 0; g = 0; h = 0;
  Coordinate parenttemp;
  parenttemp = parent;
  int xtemp = x;
  int ytemp = y;

  // from start to here using parents path
  while ( (xtemp != start.x) || (ytemp != start.y) )
  {
    if ( (parenttemp.x != xtemp) && (parenttemp.y != ytemp) )
    {
      g = g + 14.0;
    } else {
      g = g + 10.0;
    }
    xtemp = parenttemp.x;
    ytemp = parenttemp.y;
    parenttemp = field[parenttemp.y][parenttemp.x]->getParent();
  }

  // from here to finish
  h = sqrt((end.x-x)*(end.x-x)+(end.y-y)*(end.y-y))*14.0;
  // total cost
  f = g + h;
  //	cout << "(" << x << "," << y << ") : " << "f = " << f << " g = " << g << " h = " << h << endl;
}


void
Node::resetFGH()
{
  f = 10000.0;
  g = 10000.0;
  h = 20000.0;
}


double
Node::getG()
{
  return g;
}


double
Node::getF()
{
  return f;
}
