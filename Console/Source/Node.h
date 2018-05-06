#pragma once
#include <math.h>
struct Location
{
	int x, y;
	Location() { x = y = 0; }
	Location(int col, int row)
	{
		x = col;
		y = row;
	}
};

class Node
{
	int currentX, currentY;
	int g, f;
public:
	Node();
	~Node();
	Node(Location, int, int);

	void updateG();
	int getF() const;
	int getG() const;
	void calcF(Location);
	int heuristic(Location);
	Location getLocation() const;
	friend bool operator<(const Node& a, const Node& b) { return a.getF() > b.getF(); }
};

