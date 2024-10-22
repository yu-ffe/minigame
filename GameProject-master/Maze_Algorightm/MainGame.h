#pragma once

#include "Board.h"
#include "Player.h"

class MainGame {
	Board* board;
	int _size;
	Player* player;
public:
	MainGame(int size)
	: _size(size){
		player = new Player(1, 1, "HongJiHyun");
		board = new Board(_size, player);
	}
	void Play() {
		board->PlayerMoveEvent();
	}
};