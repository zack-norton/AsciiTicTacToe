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
	bool isRunning = true;
	bool isXTurn = true; //x goes first
	this->DrawBoard();

	while (isRunning) {
		if (isXTurn) {
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
			std::cout << "0 player move: " << endl;
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
					board[move[0]][move[1]] = 2;
					isXTurn = !isXTurn;
				}
				else {
					//can't play
					std::cout << "Can't overwrite another move!" << endl;
					continue;
				}
			}
		}
		if (this->CheckWinState()) {
			isRunning = false;
		}
		this->DrawBoard();
	}

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
	else if (this->board[1][0] != 0) {
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
	else if (this->board[2][0] != 0) {
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
	else if (this->board[0][0] != 0) {
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
	else if (this->board[0][1] != 0) {
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
	else if (this->board[0][2] != 0) {
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
	else if (this->board[0][0] != 0) {
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
	else if (this->board[2][0] != 0) {
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