
int MIN_INFINITY = -999999;
int MAX_INFINITY = 999999;

bool checkComplete(int *board) {
	for (int i = 0; i < 9; i++)
	{
		if (board[i] == NONE)
			return false;
	}
	return true;
}

//Need to change status for game for either end result or minmax purposes
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

bool doPrune(bool prune, int alpha, int beta) {
	if (!prune)
		return true;

	if (alpha <= beta)
		return true;
	else
		return false;
}

//Minmax with option to prune using alpha-beta pruning
int minmax_prune_opt(int *board, int turn, bool prune, int alpha, int beta) {
	int status = game_status(board);
	int value, optimal;

	//Check for terminal nodes
	if (status == X || status == O || checkComplete(board))
		return statusSwap(status);

	//Maximizer
	if (turn == X) {
		optimal = MIN_INFINITY;
		for (int i = 0; i < 9 && doPrune(prune, alpha, beta); i++) {
			if (board[i] == NONE)
			{
				board[i] = X;
				value = minmax_prune_opt(board, O, prune, alpha, beta);
				if (value >= optimal)
					optimal = value;
				board[i] = NONE;

				if (prune)
				{
					//Prune solution space
					if (optimal > alpha)
						alpha = optimal;
					if (optimal == statusSwap(X))
						break;
				}
			}
		}
	}
	//Minimizer
	else {
		optimal = MAX_INFINITY;
		for (int i = 0; i < 9 && doPrune(prune, alpha, beta); i++) {
			if (board[i] == NONE)
			{
				board[i] = O;
				value = minmax_prune_opt(board, X, prune, alpha, beta);
				if (value <= optimal)
					optimal = value;
				board[i] = NONE;

				if (prune)
				{
					//Prune solution space
					if (optimal < beta)
						beta = optimal;
					if (optimal == statusSwap(O))
						break;
				}
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
	return statusSwap(minmax_prune_opt(board, turn, false, MIN_INFINITY, MAX_INFINITY));
}

int abprun_tictactoe(int *board, int turn)
{
	//put your code here:
	//it must return X(1), O(2) or NONE(0) for tie.
	//use the function game_status(board), to evaluate a board
	//it returns X(1) if X wins, O(2) if O wins or NONE(0) if tie or game is not finished
	//the program will keep track of the number of boards evaluated
	//int result = game_status(board);
	return statusSwap(minmax_prune_opt(board, turn, true, MIN_INFINITY, MAX_INFINITY));
}
