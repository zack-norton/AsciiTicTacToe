#pragma once
#include <iostream>

using namespace std;

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
};