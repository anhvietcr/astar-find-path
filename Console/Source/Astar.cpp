#include "Astar.h"

Astar::Astar()
{
}

Astar::~Astar()
{
}

void Astar::startAstar(char* input)
{
	//open input data
	in.open(input, std::ios::in);
	if (!in) return;

	//init buffer
	this->buff = "";
	this->i = this->j = 0;

	/*
		mark map
		0	: valid
		1	: not valid (wall)
		2	: start
		3	: end
	*/
	while (std::getline(in, buff)) {
		n = buff.length();
		for (j = 0; j < n; j++) {
			if (buff[j] == ' ') map[i][j] = 0;
			else map[i][j] = 1;

			//position start, end
			if (buff[j] == 'P' || buff[j] == 'p') {
				start.x = i;
				start.y = j;
				map[i][j] = 2;
			}
			if (buff[j] == 'G' || buff[j] == 'g') {
				end.x = i;
				end.y = j;
				map[i][j] = 3;
			}
		}
		i++;
	}
	m = i;

	//init default matrix value = 0
	memset(openNodes, 0, sizeof(openNodes));
	memset(closeNodes, 0, sizeof(closeNodes));

	//find path using A*
	std::string path = findPath(start, end);
	
	//draw result map
	drawPath(path);
}

//Astar algorithm
std::string Astar::findPath(Location start, Location end)
{
	std::priority_queue<Node> q;
	static Node *Node1, *Node2;
	static int row, col, iNext, jNext;
	static char c;

	//push position start into queue
	Node1 = new Node(start, 0, 0);
	Node1->calcF(end);
	q.push(*Node1);

	//Search
	while (!q.empty()) {
		//get node with lowest F value from open Node
		Node1 = new Node(q.top().getLocation(), q.top().getG(), q.top().getF());

		//get position select top node
		row = Node1->getLocation().x;
		col = Node1->getLocation().y;

		//remove node from openlist
		q.pop();
		openNodes[row][col] = 0;

		//mark it on closeList
		closeNodes[row][col] = 1;

		//match goal
		if (row == end.x && col == end.y) {
			//create string find path
			std::string path = "";
			while (!(row == start.x && col == start.y)) {
				j = dirMap[row][col];
				c = '0' + (j + NDIR / 2) % NDIR;
				path = c + path;
				row += iDir[j];
				col += jDir[j];
			}
			delete Node1;

			//remove left node if exists
			while (!q.empty()) q.pop();

			return path;
		}
		/* move to right -> down -> left -> top
		i directions: {1, 0, -1, 0}
		j directions: {0, 1, 0, -1}
		*/
		for (i = 0; i < NDIR; i++) {
			iNext = row + iDir[i];
			jNext = col + jDir[i];

			//position valid in map
			if (!(map[iNext][jNext] == 1 || closeNodes[iNext][jNext] == 1
				  || iNext < 0 || iNext > m - 1
				  || jNext < 0 || jNext > n - 1)) {

				//generate a child node
				Node2 = new Node(Location(iNext, jNext), Node1->getG(), Node1->getF());
				Node2->updateG();
				Node2->calcF(end);

				//add to open list if not exist
				if (openNodes[iNext][jNext] == 0) {
					openNodes[iNext][jNext] = Node2->getF();
					q.push(*Node2);

					//mark parrent node
					dirMap[iNext][jNext] = (i + NDIR / 2) % NDIR;
				} else {
					delete Node2;
				}
			}
		}
		delete Node1;
	}
	return "";
}
void Astar::drawPath(std::string path)
{
	if (path.length() > 0) {
		char c;
		int k, x;
		int i = start.x;
		int j = start.y;

		map[i][j] = 2;
		for (k = 0; k < path.length(); k++) {
			c = path.at(k);
			x = atoi(&c);
			i = i + iDir[x];
			j = j + jDir[x];
			if (c == '0')
				map[i][j] = 4;
			if (c == '2')
				map[i][j] = 6;
			if (c == '1')
				map[i][j] = 7;
			if (c == '3')
				map[i][j] = 5;
		}
		map[i][j] = 3;

		// display path
		for (i = 0; i < m; i++) {
			for (j = 0; j < n; j++) {
				std::cout << std::setw(2);
				if (map[i][j] == 1) {
					Textcolor(7);
					std::cout << "o";
				} else if (map[i][j] == 0) {
					Textcolor(7);
					std::cout << " "; //not correct path
				} else if (map[i][j] == 2) {
					Textcolor(12);
					std::cout << "P"; //start
				} else if (map[i][j] == 3) {
					Textcolor(12);
					std::cout << "G"; //goal
				} else if (map[i][j] == 4) {
					Textcolor(14);
					std::cout << "v"; //path |
				} else if (map[i][j] == 5) {
					Textcolor(14);
					std::cout << "<"; //path _
				} else if (map[i][j] == 6) {
					Textcolor(14);
					std::cout << "^"; //path |
				} else if (map[i][j] == 7) {
					Textcolor(14);
					std::cout << ">"; //path _
				}
			}
			std::cout << "\n";
		}
	}
}

//Hàm tô màu
void Astar::Textcolor(int x)
{
	HANDLE mau;
	mau = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau, x);
}