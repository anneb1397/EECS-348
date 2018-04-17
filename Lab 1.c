int startX, startY;

struct Node {
	int x;
	int y;
};

bool visited[MAP_HEIGHT][MAP_WIDTH];

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

bool dfs(int **map, int x, int y) {
	bool found = false;

	if (map[y][x] == 3)
		found = true;
	else {
		if (map[y][x] == 1 || map[y][x] == 4 || map[y][x] == 5)
			found = false;

		map[y][x] = 4;
		if (isValid(map, x + 1, y))
			found = dfs(map, x + 1, y);
		if (!found && isValid(map, x, y + 1))
			found = dfs(map, x, y + 1);
		if (!found && isValid(map, x - 1, y))
			found = dfs(map, x - 1, y);
		if (!found && isValid(map, x, y - 1))
			found = dfs(map, x, y - 1);
	}

	if (found)
		map[y][x] = 5;

	return found;
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

bool bfs(int **map, int x, int y) {
	bool found = false;

	//Initialize queue and variables
	int queue[MAP_HEIGHT*MAP_WIDTH][3];
	int head = 0, tail = 0;						//head is also a parent in this case, tail is the end of the queue
	int currx = x, curry = y;
	queue[head][0] = y;							//Add start node to queue as both head and tail
	queue[head][1] = x;
	queue[head][2] = -1;
	queue[tail][0] = y;
	queue[tail][1] = x;
	queue[tail][2] = -1;

	tail++;

	while (!found && head < tail) {
		//Update x and y
		curry = queue[head][0];
		currx = queue[head][1];

		//Check for goal
		if (map[curry][currx] == 3)
		{
			found = true;
			break;
		}

		//Update map and visited
		map[curry][currx] = 4;
		visited[curry][currx] = true;

		//Expand the current node
		for (int i = 0; i < 4; i++) {
			Node n = expand(currx, curry, i);
			int nx = n.x, ny = n.y;
			//Check for validity and redundancy
			if (isValid(map, nx, ny) && !visited[ny][nx]) {
				queue[tail][0] = ny;
				queue[tail][1] = nx;
				queue[tail][2] = head;
				tail++;
			}
		}

		//Update head
		head++;
	}

	//Change the path to be 5
	if (found) {
		while (queue[head][2] != -1) {
			curry = queue[head][0];
			currx = queue[head][1];
			map[curry][currx] = 5;
			head = queue[head][2];
		}
		//Change starting position too (parent = -1)
		map[y][x] = 5;
	}

	return found;
}

bool df_search(int **map)
{
	// PUT YOUR CODE HERE
	// access the map using "map[y][x]"
	// y between 0 and MAP_HEIGHT-1
	// x between 0 and MAP_WIDTH-1
	reset();
	findStart(map);
	return dfs(map, startX, startY);
}

bool bf_search(int **map)
{
	// PUT YOUR CODE HERE
	// access the map using "map[y][x]"
	// y between 0 and MAP_HEIGHT-1
	// x between 0 and MAP_WIDTH-1
	reset();
	findStart(map);
	return bfs(map, startX, startY);
}