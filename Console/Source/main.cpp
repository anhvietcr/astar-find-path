#include "Astar.h"

int main(int argc, char * argv[])
{
	Astar *star = new Astar();

	star->startAstar(argv[1]);
	
	return 0;
}