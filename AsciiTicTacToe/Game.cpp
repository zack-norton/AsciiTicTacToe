#include "Game.h"


Game::Game() {
	
}

Game::Game(const Game& game2) {

}

Game::~Game() {

}

void Game::DrawBoard() {
	//0,0
	Game::DrawPosition(board[0][0]);
	

	//vertical line
	std::cout << "|";

	//0,1
	Game::DrawPosition(board[0][1]);
	//vertical line
	std::cout << "|";

	//0,2
	Game::DrawPosition(board[0][2]);
	//new line
	std::cout << endl;
	std::cout << "-----" << endl;

	//1,0
	Game::DrawPosition(board[1][0]);
	//vertical line
	std::cout << "|";

	//1,1
	Game::DrawPosition(board[1][1]);
	//vertical line
	std::cout << "|";

	//1,2
	Game::DrawPosition(board[1][2]);
	//new line
	std::cout << endl;
	std::cout << "-----" << endl;

	//2,0
	Game::DrawPosition(board[2][0]);
	//vertical line
	std::cout << "|";
	//2,1
	Game::DrawPosition(board[2][1]);
	//vertical line
	std::cout << "|";

	//2,2
	Game::DrawPosition(board[2][2]);

	std::cout << endl;
}

void Game::DrawPosition(unsigned short value) {
	if (value == 0) {
		//empty
		std::cout << " ";
	}
	else if (value == 1) {
		//X
		std::cout << "X";
	}
	else if (value == 2) {
		//O
		std::cout << "O";
	}
}

void Game::Play() {
	cout.flush();

	bool isSinglePlayer = false;
	this->DrawBoard();

	//1 or 2 player?
	std::cout << "1 or 2 player game?" << endl;
	std::string oneOrTwo;
	std::cin >> oneOrTwo;

	if (oneOrTwo.compare("1") == 0) {
		isSinglePlayer = true;
	}

	if (isSinglePlayer) {
		//launch single player game
		std::cout << "Single Player Game" << endl;
		this->Game::SinglePlayerGame();
	}
	else {
		//launch two player game
		std::cout << "Two Player Game" << endl;
		this->Game::TwoPlayerGame();
	}


	

}

void Game::SinglePlayerGame() {
	bool isRunning = true;
	bool isXTurn = true;

	while (isRunning) {
		if (isXTurn) {
			//player 1
			std::cout << "X player move: " << endl;

			string input;
			std::cin >> input;

			if (input.compare("exit") == 0 || input.compare("quit") == 0) {
				//quit game
				isRunning = false;
				break;
			}
			else {
				std::vector<string> moveStr = Game::split(input, ',');
				int move[2];

				move[0] = std::stoi(moveStr[0]);
				move[1] = std::stoi(moveStr[1]);

				if (board[move[0]][move[1]] == 0) {
					//play
					board[move[0]][move[1]] = 1;
					
					isXTurn = !isXTurn;
				}
				else {
					//can't play
					std::cout << "Can't overwrite another move!" << endl;
					continue;
				}
			}

			
		}
		else {
			//ai move
			std::cout << "O player move: " << endl;

			//find minimax best move
			Move move = Game::FindBestMove();
			
			board[move.x][move.y] = 2;

			std::cout << move.x << "," << move.y << endl;

			isXTurn = !isXTurn;
		}

		if (this->CheckWinState()) {
			isRunning = false;
		}

		if (this->CheckDraw()) {
			isRunning = false;
		}

		this->DrawBoard();
	}
}

void Game::TwoPlayerGame() {
	bool isRunning = true;
	bool isXTurn = true; //x goes first

	while (isRunning) {
		if (isXTurn) {
			std::cout << "X player move: " << endl;
		}
		else {
			std::cout << "O player move: " << endl;
		}

		string input;
		std::cin >> input;

		if (input.compare("exit") == 0 || input.compare("quit") == 0) {
			//quit game
			isRunning = false;
			break;
		}
		else {
			std::vector<string> moveStr = Game::split(input, ',');
			int move[2];

			move[0] = std::stoi(moveStr[0]);
			move[1] = std::stoi(moveStr[1]);

			if (board[move[0]][move[1]] == 0) {
				if (isXTurn) {
					//play
					board[move[0]][move[1]] = 1;
				}
				else {
					//play
					board[move[0]][move[1]] = 2;
				}
				isXTurn = !isXTurn;
			}
			else {
				//can't play
				std::cout << "Can't overwrite another move!" << endl;
				continue;
			}
		}

		if (this->CheckWinState()) {
			isRunning = false;
		}

		if (this->CheckDraw()) {
			isRunning = false;
		}

		this->DrawBoard();
	}
}

Move Game::FindBestMove() {
	Move bestMove;
	bestMove.x = -1;
	bestMove.y = -1;
	int bestValue = -1000;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (this->board[i][j] == 0) {
				this->board[i][j] = 2;

				int moveValue = MiniMax(0, false);

				this->board[i][j] = 0;

				if (moveValue > bestValue) {
					bestMove.x = i;
					bestMove.y = j;
					bestValue = moveValue;
				}
			}
		}
	}

	return bestMove;
}

int Game::MiniMax(int depth, bool isMax) {

	int score = evaluate();

	// If Maximizer has won the game return his/her 
	// evaluated score 
	if (score == 10)
		return score;

	// If Minimizer has won the game return his/her 
	// evaluated score 
	if (score == -10)
		return score;

	// If there are no more moves and no winner then 
	// it is a tie 
	if (isMovesLeft() == false)
		return 0;

	if (isMax) {
		int best = -1000;

		// Traverse all cells 
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				// Check if cell is empty 
				if (board[i][j] == 0)
				{
					// Make the move 
					board[i][j] = 1;

					// Call minimax recursively and choose 
					// the maximum value 
					best = max(best,
						MiniMax(depth + 1, !isMax));

					// Undo the move 
					board[i][j] = 0;
				}
			}
		}
		return best;
	}
	else {
		int best = 1000;

		// Traverse all cells 
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				// Check if cell is empty 
				if (board[i][j] == 0)
				{
					// Make the move 
					board[i][j] = 2;

					// Call minimax recursively and choose 
					// the minimum value 
					best = min(best,
						MiniMax(depth + 1, !isMax));

					// Undo the move 
					board[i][j] = 0;
				}
			}
		}
		return best;
	}
}

int Game::evaluate() {
	// Checking for Rows for X or O victory. 
	for (int row = 0; row < 3; row++)
	{
		if (this->board[row][0] == this->board[row][1] &&
			this->board[row][1] == this->board[row][2])
		{
			if (this->board[row][0] == 1)
				return +10;
			else if (this->board[row][0] == 2)
				return -10;
		}
	}

	// Checking for Columns for X or O victory. 
	for (int col = 0; col < 3; col++)
	{
		if (this->board[0][col] == this->board[1][col] &&
			this->board[1][col] == this->board[2][col])
		{
			if (this->board[0][col] == 1)
				return +10;

			else if (this->board[0][col] == 2)
				return -10;
		}
	}

	// Checking for Diagonals for X or O victory. 
	if (this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2])
	{
		if (this->board[0][0] == 1)
			return +10;
		else if (this->board[0][0] == 2)
			return -10;
	}

	if (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0])
	{
		if (this->board[0][2] == 1)
			return +10;
		else if (this->board[0][2] == 2)
			return -10;
	}

	// Else if none of them have won then return 0 
	return 0;
}

bool Game::isMovesLeft() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (this->board[i][j] == 0) {
				return true;
			}
		}
	}

	return false;
}

bool Game::CheckWinState() {
	bool isWinner = false;
	//horizontal rows
	if (this->board[0][0] != 0) {
		//check 0 row columns
		if (this->board[0][0] == this->board[0][1] && this->board[0][1] == this->board[0][2]) {
			//top row won
			//check who won
			if (this->board[0][0] == 1) {
				//x won
				std::cout << "X player won!" << endl;
				isWinner = true;
			}
			else {
				//O won
				std::cout << "O player won!" << endl;
				isWinner = true;
			}
		}
	}
	if (this->board[1][0] != 0) {
		//check 1 row columns
		if (this->board[1][0] == this->board[1][1] && this->board[1][1] == this->board[1][2]) {
			//middle row won
			//check who won
			if (this->board[1][0] == 1) {
				//x won
				std::cout << "X player won!" << endl;
				isWinner = true;
			}
			else {
				//O won
				std::cout << "O player won!" << endl;
				isWinner = true;
			}
		}
	}
	if (this->board[2][0] != 0) {
		//check 2 row columns
		if (this->board[2][0] == this->board[2][1] && this->board[2][1] == this->board[2][2]) {
			//bottom row won
			//check who won
			if (this->board[2][0] == 1) {
				//x won
				std::cout << "X player won!" << endl;
				isWinner = true;
			}
			else {
				//O won
				std::cout << "O player won!" << endl;
				isWinner = true;
			}
		}
	}
	//vertical columns
	if (this->board[0][0] != 0) {
		//check 0 column rows
		if (this->board[0][0] == this->board[1][0] && this->board[1][0] == this->board[2][0]) {
			//left column won
			//check who won
			if (this->board[0][0] == 1) {
				//x won
				std::cout << "X player won!" << endl;
				isWinner = true;
			}
			else {
				//O won
				std::cout << "O player won!" << endl;
				isWinner = true;
			}
		}
	}
	if (this->board[0][1] != 0) {
		//check 1 columns rows
		if (this->board[0][1] == this->board[1][1] && this->board[1][1] == this->board[2][1]) {
			//middle column won
			//check who won
			if (this->board[0][1] == 1) {
				//x won
				std::cout << "X player won!" << endl;
				isWinner = true;
			}
			else {
				//O won
				std::cout << "O player won!" << endl;
				isWinner = true;
			}
		}
	}
	if (this->board[0][2] != 0) {
		//check 2 columns rows
		if (this->board[0][2] == this->board[1][2] && this->board[1][2] == this->board[2][2]) {
			//right column won
			//check who won
			if (this->board[0][2] == 1) {
				//x won
				std::cout << "X player won!" << endl;
				isWinner = true;
			}
			else {
				//O won
				std::cout << "O player won!" << endl;
				isWinner = true;
			}
		}
	}
	//diagonal
	if (this->board[0][0] != 0) {
		//check 0 diagonal
		if (this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2]) {
			
			//check who won
			if (this->board[0][0] == 1) {
				//x won
				std::cout << "X player won!" << endl;
				isWinner = true;
			}
			else {
				//O won
				std::cout << "O player won!" << endl;
				isWinner = true;
			}
		}
	}
	if (this->board[2][0] != 0) {
		//check 2 row diagonal
		if (this->board[2][0] == this->board[1][1] && this->board[1][1] == this->board[0][2]) {
			
			//check who won
			if (this->board[2][0] == 1) {
				//x won
				std::cout << "X player won!" << endl;
				isWinner = true;
			}
			else {
				//O won
				std::cout << "O player won!" << endl;
				isWinner = true;
			}
		}
	}
	return isWinner;
}

bool Game::CheckDraw() {
	bool isDraw = true;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (this->board[i][j] == 0) {
				isDraw = false;
			}
		}
	}

	if (isDraw) {
		std::cout << "Draw Game!" << endl;
	}

	return isDraw;
}

std::vector<string> Game::split(const std::string& text, char separator) {
	std::vector<std::string> tokens;
	std::size_t start = 0, end = 0;
	while ((end = text.find(separator, start)) != std::string::npos) {
		tokens.push_back(text.substr(start, end - start));
		start = end + 1;
	}
	tokens.push_back(text.substr(start));
	return tokens;
}