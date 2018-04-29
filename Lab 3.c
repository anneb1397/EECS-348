
bool checkComplete(int *board) {
	for (int i = 0; i < 9; i++)
	{
		if (board[i] == NONE)
			return false;
	}
	return true;
}

int statusSwap(int status) {
	if (status == X)
		status = 1;
	else if (status == O)
		status = -1;
	else if (status == 1)
		status = X;
	else if (status == -1)
		status = O;

	return status;
}

int minmax(int  *board, int turn) {
	int status = game_status(board);
	int value, optimal;

	if (status == X || status == O || checkComplete(board))
		return statusSwap(status);

	//Maximizer
	if (turn == X) {
		optimal = -999999;
		for (int i = 0; i < 9; i++) {
			if (board[i] == NONE)
			{
				board[i] = X;
				value = minmax(board, O);
				if (value >= optimal)
					optimal = value;
				board[i] = NONE;
			}
		}
	}
	//Minimizer
	else {
		optimal = 999999;
		for (int i = 0; i < 9; i++) {
			if (board[i] == NONE)
			{
				board[i] = O;
				value = minmax(board, X);
				if (value <= optimal)
					optimal = value;
				board[i] = NONE;
			}
		}
	}

	return optimal;
}


int minmax_tictactoe(int *board, int turn)
{
	//put your code here:
	//it must return X(1), O(2) or NONE(0) for tie.
	//use the function game_status(board), to evaluate a board
	//it returns X(1) if X wins, O(2) if O wins or NONE(0) if tie or game is not finished
	//the program will keep track of the number of boards evaluated
	//int result = game_status(board);
	return statusSwap(minmax(board, turn));
}

int abprun_tictactoe(int *board, int turn)
{
	//put your code here:
	//it must return X(1), O(2) or NONE(0) for tie.
	//use the function game_status(board), to evaluate a board
	//it returns X(1) if X wins, O(2) if O wins or NONE(0) if tie or game is not finished
	//the program will keep track of the number of boards evaluated
	//int result = game_status(board);
	return NONE;
}
