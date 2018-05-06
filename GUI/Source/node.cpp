#include "node.h"

Node::Node(Location loc, int g, int f)
{
    currentX = loc.x;
    currentY = loc.y;
    this->g = g;
    this->f = f;
}

void Node::updateG()
{
    this->g += 1;
}

int Node::getF() const
{
    return this->f;
}
int Node::getG() const
{
    return this->g;
}
void Node::calcF(Location des)
{
    this->f = this->g + this->heuristic(des);
}

int Node::heuristic(Location des)
{
    return abs(currentX - des.x) + abs(currentY - des.y);
}

Location Node::getLocation() const
{
    return Location(currentX, currentY);
}
