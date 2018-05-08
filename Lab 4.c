int counter;

//Checks the constraints of sudoku
//1. Does row contain value?
//2. Does column contain value?
//3. Does square contain value?
bool checkConstraints(int **sudoku, int x, int y, int value) {
	for (int i = 0; i < 9; i++)
	{
		if (sudoku[y][i] == value || sudoku[i][x] == value || sudoku[(y / 3) * 3 + i / 3][(x / 3) * 3 + i % 3] == value)
			return false;
	}
	return true;
}

///Checks to see if puzzle has been completed
bool checkPuzzle(int **sudoku) {
	for (int y = 0; y < 9; y++) {
		for (int x = 0; x < 9; x++) {
			if (sudoku[y][x] == 0)
				return false;
		}
	}
	return true;
}

//Recursive depth-first backtracking algorithm
bool backtrack(int **sudoku) {
	//is the solution complete?
	if (checkPuzzle(sudoku))
		return true;

	for (int y = 0; y < 9; y++) {
		for (int x = 0; x < 9; x++) {
			if (sudoku[y][x] == 0)
			{
				//Update space
				counter++;
				for (int i = 1; i < 10; i++) {
					//Check constraints
					if (checkConstraints(sudoku, x, y, i)) {
						
						//Change value
						sudoku[y][x] = i;
						//recurse
						if (backtrack(sudoku))
							return true;

						//Backtrack was unsuccessful, set to 0, go to next value
						sudoku[y][x] = 0;
					}
				}
				//The backtrack has failed every time, return false for invalid solution
				return false;
			}
		}
	}
}

bool forward(int **sudoku) {
	for (int y = 0; y < 9; y++) {
		for (int x = 0; x < 9; x++) {
			if (sudoku[y][x] == 0)
			{
				for (int i = 1; i < 10; i++) {
					if (checkConstraints(sudoku, x, y, i))
					{
						counter++;
						sudoku[y][x] = i;

						if (forward(sudoku))
							return true;
						
						sudoku[y][x] = 0;
					}
				}
				//Invalid solution, could not satisfy constraints with choice
				return false;
			}
		}
	}
	//Board is complete
	return true;
}

//Count the number of legal values left
int values(int **sudoku, int x, int y) {
	int count = 9;

	for (int v = 1; v < 10; v++) {
		if(!checkConstraints(sudoku, x, y, v))
				count--;
	}

	return count;
}

//Find the minimum number of legal values for the board
int minimum(int **sudoku) {
	int min = 9;
	for (int y = 0; y < 9; y++) {
		for (int x = 0; x < 9; x++) {
			if (sudoku[y][x] == 0 && values(sudoku, x, y) < min)
				min = values(sudoku, x, y);
		}
	}

	return min;
}

///Similar to forward checking but with additional min value requirements
bool mrv(int **sudoku) {
	//Find the minimum value
	int min = minimum(sudoku);
	for (int y = 0; y < 9; y++) {
		for (int x = 0; x < 9; x++) {
			//Check to see if the space is the min for this point
			if (sudoku[y][x] == 0 && values(sudoku, x, y) == min)
			{
				//Same as forward
				for (int i = 1; i < 10; i++) {
					if (checkConstraints(sudoku, x, y, i))
					{
						counter++;
						sudoku[y][x] = i;

						if (mrv(sudoku))
							return true;

						sudoku[y][x] = 0;
					}
				}
				return false;
			}
		}
	}
	return true;
}

int sudoku_backtracking(int **sudoku)
{
	// PUT YOUR CODE HERE
	// access the sudoku using "sudoku[y][x]"
	// y between 0 and 9
	// x between 0 and 9
	// function must return the number of permutations performed
	// the use of counter to keep track of the worlds 
	// explored is optional but recommended 
	counter=0;
	bool b = backtrack(sudoku);
	return counter;
}

int sudoku_forwardchecking(int **sudoku)
{
	// PUT YOUR CODE HERE
	// access the sudoku using "sudoku[y][x]"
	// y between 0 and 9
	// x between 0 and 9
	// function must return the number of permutations performed
	// the use of counter to keep track of the worlds 
	// explored is optional but recommended 
	counter=0;
	bool b = forward(sudoku);
	return counter;
}

int sudoku_mrv(int **sudoku)
{
	// PUT YOUR CODE HERE
	// access the sudoku using "sudoku[y][x]"
	// y between 0 and 9
	// x between 0 and 9
	// function must return the number of permutations performed
	// the use of counter to keep track of the worlds 
	// explored is optional but recommended 
	counter=0;
	bool b = mrv(sudoku);
	return counter;
}

