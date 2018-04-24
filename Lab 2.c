#include <string.h>
#include <stdlib.h>

int startX, startY;
int goalX, goalY;
int head, tail;

bool visited[MAP_HEIGHT][MAP_WIDTH];

//y, x,parent, manhattendistance, distance from start
int queue[MAP_HEIGHT*MAP_WIDTH][5];

struct Node {
	int x;
	int y;
};

void reset() {
	for (int y = 0; y < MAP_HEIGHT; y++)
		for (int x = 0; x < MAP_WIDTH; x++)
			visited[y][x] = false;
}

void findStart(int **map) {
	for (int y = 0; y < MAP_HEIGHT; y++)
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			if (map[y][x] == 2)
			{
				startX = x;
				startY = y;
				map[y][x] = 5;
				break;
			}
		}
}

void findGoal(int **map) {
	for (int y = 0; y < MAP_HEIGHT; y++)
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			if (map[y][x] == 3)
			{
				goalX = x;
				goalY = y;
				return;
			}
		}
}

bool isValid(int **map, int x, int y) {
	if (x < 0 || x > MAP_WIDTH - 1 || y < 0 || y > MAP_HEIGHT - 1)
		return false;
	else if (map[y][x] == 0 || map[y][x] == 3)
		return true;
	else {
		visited[y][x] = true;
		return false;
	}
}

int ManhattenDistance(Node n) {
	int nx = n.x, ny = n.y;
	int md = 0;

	if (nx > goalX)
		md += nx - goalX;
	else
		md += goalX - nx;

	if (ny > goalY)
		md += ny - goalY;
	else
		md += goalY - ny;

	return md;
}

void initializeQueue() {
	Node n;
	n.x = startX;
	n.y = startY;
	queue[0][0] = startY;
	queue[0][1] = startX;
	queue[0][2] = -1;
	queue[0][3] = ManhattenDistance(n);
	queue[0][4] = 0;
}

int min(int num1, int num2) {
	if (num1 < num2)
		return num1;
	else if (num2 < num1)
		return num2;
	else
		return num1;
}

int TieBreak(int index1, int index2) {
	if (queue[index1][1] == queue[index2][1])
		return ((queue[index1][0] < queue[index2][0]) ? index1 : index2);
	else
		return ((min(queue[index1][1], queue[index2][1]) == queue[index1][1]) ? index1 : index2);
}

Node expand(int x, int y, int index) {
	int tempx = x, tempy = y;
	switch (index) {
	case 0:
		tempx = x + 1;
		break;
	case 1:
		tempy = y + 1;
		break;
	case 2:
		tempx = x - 1;
		break;
	case 3:
		tempy = y - 1;
		break;
	}
	Node n;
	n.x = tempx;
	n.y = tempy;
	return n;
}

int ScanFrontier() {
	int minIndex = 0;
	int currIndex = 0;
	int minMD = queue[currIndex][3];
	int currX = queue[currIndex][1], currY = queue[currIndex][0];
	bool minFound = false;

	while (currIndex < tail) {
		currX = queue[currIndex][1];
		currY = queue[currIndex][0];

		if (!visited[currY][currX]) {
			if (queue[currIndex][3] < minMD)
			{
				minIndex = currIndex;
				minMD = queue[minIndex][3];
			}
			else if (queue[currIndex][3] == minMD) {
				minIndex = TieBreak(minIndex, currIndex);
				minMD = queue[minIndex][3];

			}
			if (!minFound) {
				minIndex = currIndex;
				minMD = queue[minIndex][3];
			}
			minFound = true;
		}
		currIndex++;
	}

	if (!minFound) {
		minIndex = tail;
	}

	return minIndex;
}

bool astar(int **map) {
	bool found = false;
	head = 0;
	tail = 1;
	int currX = startX, currY = startY;
	int currIndex = 0;						//Track the curr index of the frontier
	int md;

	int iterations = 0;

	while (!found && currIndex < tail) {
		//set current
		currY = queue[currIndex][0];
		currX = queue[currIndex][1];
		md = queue[currIndex][4];

		//check goal
		if (map[currY][currX] == 3) {
			found = true;
			break;
		}

		//Update map and visited
		map[currY][currX] = 4;
		visited[currY][currX] = true;

		//Expand the current node
		for (int i = 0; i < 4; i++) {
			Node n = expand(currX, currY, i);
			int nx = n.x, ny = n.y;
			//Check for validity and redundancy
			if (isValid(map, nx, ny) && !visited[ny][nx]) {
				queue[tail][0] = ny;
				queue[tail][1] = nx;
				queue[tail][2] = currIndex;
				queue[tail][3] = md + 1 + ManhattenDistance(n);
				queue[tail][4] = md + 1;
				tail++;
			}
		}
		//Scan frontier for lowest 
		//Tie Break if necessary
		//Update currIndex
		currIndex = ScanFrontier();
	}


	//Change the path to be 5
	if (found) {
		while (queue[currIndex][2] != -1) {
			currY = queue[currIndex][0];
			currX = queue[currIndex][1];
			map[currY][currX] = 5;
			currIndex = queue[currIndex][2];
		}
		//Change starting position too (parent = -1)
		map[startY][startX] = 5;
	}

	return found;
}

bool astar_search(int **map)
{
	bool found = false;
	// PUT YOUR CODE HERE
	// access the map using "map[y][x]"
	// y between 0 and MAP_HEIGHT-1
	// x between 0 and MAP_WIDTH-1
	reset();
	findStart(map);
	findGoal(map);
	initializeQueue();
	return astar(map);
}
