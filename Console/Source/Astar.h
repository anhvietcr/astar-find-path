#pragma once
#include "Node.h"

#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <Windows.h>
#include <iomanip>

#define MAX_ROW 100
#define MAX_COL 100
#define NDIR 4

class Astar
{
	//init map
	std::ifstream in;
	std::string buff;
	int i, j, m, n;
	Location start, end;

	//director for node, {right, down, left, top}
	const int iDir[NDIR] = { 1, 0, -1, 0 };
	const int jDir[NDIR] = { 0, 1, 0, -1 };

	//init storage
	int map[MAX_ROW][MAX_COL];
	int openNodes[MAX_ROW][MAX_COL];
	int closeNodes[MAX_ROW][MAX_COL];
	int dirMap[MAX_ROW][MAX_COL];

public:
	Astar();
	~Astar();
	void startAstar(char*);
	std::string findPath(Location, Location);
	void drawPath(std::string);
	void Textcolor(int x);
};

