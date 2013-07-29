/*
 * node.hpp
 *
 *  Created on: Apr 23, 2010
 *      Author: annom
 */

#ifndef NODE_HPP_
#define NODE_HPP_

#include <cstdlib>
#include <cmath>
#include <iostream>
#include <vector>

struct Color {
	int r;
	int g;
	int b;
};

struct Coordinate {
	int x;
	int y;
};

class Node {
private:
	int x;
	int y;
	bool wall, path;
	bool opened, closed;
	bool start, target;
	double f,g,h;
	Color color;
	Coordinate parent;

public:
	Node(int x, int y);
	int getX();
	Color getColor();
	void changeWall();
	void setWall(bool yesno);
	void setOpen(bool yesno);
	bool getOpen();
	void setClose(bool yesno);
	bool getClose();
	void setTarget(bool yesno);
	void setStart(bool yesno);
	void setPath(bool yesno);
	void updateColor();
	void tryToOpen();
	void setParent(int x, int y);
	Coordinate getParent();
	void calcFGH(Coordinate start, Coordinate end, std::vector<std::vector<Node*> > field);
	void resetFGH();
	double getG();
	double getF();
};

#endif /* NODE_HPP_ */
