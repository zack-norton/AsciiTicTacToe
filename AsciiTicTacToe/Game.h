#pragma once
#include <iostream>
#include <vector>
#include <string>

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
	void DrawPosition(unsigned short value);
	bool CheckWinState();
	bool CheckDraw();

	void Play();
	void SinglePlayerGame();
	void TwoPlayerGame();

	std::vector<string> split(const std::string& text, char separator);
};