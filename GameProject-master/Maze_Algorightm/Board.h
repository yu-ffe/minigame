#pragma once
#include <iostream>
#include <random>
#include <time.h>
#include "Player.h"

class Board :public Player::EventListner{
private:
	int _size;
	Player* _player;

public:
	Board() = delete;
	Board(int size,Player* player);
	~Board();

	void println(bool m);
	void moveCharcter(int x0, int y0, int x1, int y1);
	bool check(int x, int y);

	virtual void PlayerMoveEvent();
	
private:
	enum class TileType {
		Empty,
		Wall,
		USER = 2
	};
	enum Direction {
		LEFT,
		RIGHT,
		UP,
		DOWN
	}; 
	struct Node {
		TileType type;
		bool came;
	};
	const int DIR[4][2] = { {0,-2},{0,+2},{-2,0},{+2,0} };
	Node** _board;

	
	void GenerateByBinaryTree();	// √ ±‚ ∏  º≥¡§
	void RecursiveBackTraing(int start_X, int start_Y);		// Maze Algorithm
	void shuffleArray(int* array, int size);
	int inRange(int y, int x);
};