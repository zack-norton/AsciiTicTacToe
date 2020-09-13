#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;


struct Move {
	int x;
	int y;
};

class Game {
private:
	unsigned short board[3][3] = { 0, 0, 0,
								   0, 0, 0,
								   0, 0, 0 };
public:
	Game();
	Game(const Game &game2);
	~Game();

	void DrawBoard();
	void DrawPosition(unsigned short value);
	bool CheckWinState();
	bool CheckDraw();

	//minimax functions
	Move FindBestMove();
	int MiniMax(int depth, bool isMax);
	bool isMovesLeft();
	int evaluate();

	void Play();
	void SinglePlayerGame();
	void TwoPlayerGame();

	std::vector<string> split(const std::string& text, char separator);
};