#include "Node.h"

Node::Node() {}
Node::~Node() {}

Node::Node(Location loc, int g, int f)
{
	currentX = loc.x;
	currentY = loc.y;
	this->g = g;
	this->f = f;
}
//get g, f, position value
int Node::getF() const { return this->f; }
int Node::getG() const { return this->g; }
Location Node::getLocation() const { return Location(currentX, currentY); }

//update g value
void Node::updateG() { this->g += 1; }

//calculator f value
void Node::calcF(Location des) { this->f = g + heuristic(des); }

//manhattan
int Node::heuristic(Location des)
{
	return abs(currentX - des.x) + abs(currentY - des.y);
}
