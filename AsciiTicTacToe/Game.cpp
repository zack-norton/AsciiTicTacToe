#include "Game.h"

Game::Game() {
	
}

Game::Game(const Game& game2) {

}

Game::~Game() {

}

void Game::DrawBoard() {
	if (board[0][0] == 0) {
		//empty
		std::cout << " ";
	}
	else if (board[0][0] == 1) {
		//X
		std::cout << "X";
	}
	else if (board[0][0] == 2) {
		//O
		std::cout << "O";
	}

	//vertical line
	std::cout << "|";

	//0,1
	std::cout << " ";
	//vertical line
	std::cout << "|";

	//0,2
	std::cout << " ";
	//new line
	std::cout << endl;
	std::cout << "-----" << endl;

	//1,0
	std::cout << " ";
	//vertical line
	std::cout << "|";

	//1,1
	std::cout << " ";
	//vertical line
	std::cout << "|";

	//1,2
	std::cout << " ";
	//new line
	std::cout << endl;
	std::cout << "-----" << endl;

	//2,0
	std::cout << " ";
	//vertical line
	std::cout << "|";
	//2,1
	std::cout << " ";
	//vertical line
	std::cout << "|";

	//2,2
	std::cout << " ";

	std::cout << endl;


}