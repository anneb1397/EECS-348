float const NEG_INFINITY = -9999999;
float gdelivery_fee, gbattery_drop_cost, gdronerepair_cost, gdiscount_per_cycle;
int direction[4][2] = { 0,1,1,0,0,-1,-1,0 };
float temp[6][6];

float GetProbability(int movement, int x, int y, int dx, int dy) {
	float probability = 0;
	float OnAdjustmentInDirection = 0;
	float OnAdjustmentSides = 0;

	switch (movement) {
	case SON:
		OnAdjustmentInDirection = 0.1;
		OnAdjustmentSides = -0.05;
	case SOFF:
		if (dy == y + 1) probability = 0.7 + OnAdjustmentInDirection;
		if (dy == y - 1) probability = 0;
		if (dx == x + 1 || dx == x - 1) probability = 0.15 + OnAdjustmentSides;
		break;
	case NON:
		OnAdjustmentInDirection = 0.1;
		OnAdjustmentSides = -0.05;
	case NOFF:
		if (dy == y - 1) probability = 0.7 + OnAdjustmentInDirection;
		if (dy == y + 1) probability = 0;
		if (dx == x + 1 || dx == x - 1) probability = 0.15 + OnAdjustmentSides;
		break;
	case WON:
		OnAdjustmentInDirection = 0.1;
		OnAdjustmentSides = -0.05;
	case WOFF:
		if (dx == x - 1) probability = 0.7 + OnAdjustmentInDirection;
		if (dx == x + 1) probability = 0;
		if (dy == y + 1 || dy == y - 1) probability = 0.15 + OnAdjustmentSides;
		break;
	case EON:
		OnAdjustmentInDirection = 0.1;
		OnAdjustmentSides = -0.05;
	case EOFF:
		if (dx == x + 1) probability = 0.7 + OnAdjustmentInDirection;
		if (dx == x - 1) probability = 0;
		if (dy == y + 1 || dy == y - 1) probability = 0.15 + OnAdjustmentSides;
		break;
	}

	return probability;
}

float GetReward(int movement) {
	switch (movement) {
	case SON:
	case NON:
	case WON:
	case EON:
		return -2 * gbattery_drop_cost;
	case SOFF:
	case NOFF:
	case WOFF:
	case EOFF:
		return -1 * gbattery_drop_cost;
	}
}

float FindExits(int **map, int **policies, float **values) {
	for (int y = 0; y < 6; y++) {
		for (int x = 0; x < 6; x++) {
			if (map[y][x] == CUSTOMER) {
				values[y][x] = gdelivery_fee;
				policies[y][x] = EXIT;
			}
			if (map[y][x] == RIVAL) {
				values[y][x] = -1*gdronerepair_cost;
				policies[y][x] = EXIT;
			}
		}
	}
}

float FindNearVal(int dx, int dy, float values[6][6] = temp) {
	if (dx < 0)
		return values[dy][dx + 1];
	if (dx > 5)
		return values[dy][dx - 1];
	if (dy < 0)
		return values[dy + 1][dx];
	if (dy > 5)
		return values[dy - 1][dx];
}

bool possible(int x, int y)
{
	return (x < 6 && x >= 0 && y < 6 && y >= 0);
}

void Action(int **map, int **policies, float **values, int x, int y) {
	float q = 0.0;
	float qmax = NEG_INFINITY;
	float probability, reward, gamma = 1.0 - gdiscount_per_cycle;
	int dx, dy;
	for (int i = 1; i < 9; i++) {
		q = 0.0;
		for (int d = 0; d < 4; d++) {
			dx = x + direction[d][1];
			dy = y + direction[d][0];
			probability = GetProbability(i, x, y, dx, dy);
			reward = GetReward(i);
			
			if (possible(dx,dy))
				q += probability*(reward + gamma * temp[dy][dx]);
			else {
				if (dx > 5)
					q += probability*(reward + gamma * temp[dy][dx - 1]);
				
				if (dy > 5)
					q += probability*(reward + gamma * temp[dy - 1][dx]);
				
				if (dx < 0)
					q += probability*(reward + gamma * temp[dy][dx + 1]);
				
				if (dy < 0)
					q += probability*(reward + gamma * temp[dy + 1][dx]);
				
			}
		}

		if (q > qmax)
		{
			qmax = q;
			policies[y][x] = i;
		}

		values[y][x] = qmax;
	}
}

float flight_planner(int **map, int **policies, float **values) {
	FindExits(map, policies, values);
	int converge = 0;

	while (converge < 100)
	{
		for (int y = 0; y<6; y++) {
			for (int x = 0; x<6; x++) {
				temp[y][x] = values[y][x];
			}
		}

		for (int y = 0; y < 6; y++) {
			for (int x = 0; x < 6; x++) {
				if (map[y][x] != RIVAL && map[y][x] != CUSTOMER)
					Action(map, policies, values, x, y);
			}
		}
		converge++;
	}
	float value = 0.0;
	for (int y = 0; y < 6; y++) {
		for (int x = 0; x < 6; x++) {
			if (map[y][x] == 1)
			{
				value = values[y][x];
			}
		}
	}

	return value;
}

float drone_flight_planner (int **map, int **policies, float **values, float delivery_fee, float battery_drop_cost, float dronerepair_cost, float discount_per_cycle)
{

	// PUT YOUR CODE HERE
	// access the map using "map[y][x]"
	// access the policies using "policies[y][x]"
	// access the values using "values[y][x]"
	// y between 0 and 5
	// x between 0 and 5
	// function must return the value of the cell corresponding to the starting position of the drone
 
	gdelivery_fee = delivery_fee;
	gbattery_drop_cost = battery_drop_cost;
	gdronerepair_cost = dronerepair_cost;
	gdiscount_per_cycle = discount_per_cycle;
	
	return flight_planner(map, policies, values);
}
