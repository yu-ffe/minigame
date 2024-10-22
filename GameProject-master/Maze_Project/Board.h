#include <QtWidgets/qgraphicsScene>
//#include <QtWidgets/QgraphicsRectItem>
#include <QtWidgets/QGraphicsTextItem>
#include<iostream>

#include <qgraphicsview.h>
#include "item.h"
#include "Player.h"

class Board : public QGraphicsScene {
private:
	enum class TileType {
		Wall,
		Empty,
		USER,
		Trap
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
	int _size;
	Player* _player;
	std::vector<std::vector<Item*>> _items;
	QGraphicsRectItem _root;
	int _trap;
	

public:
	Board::Board(int size, Player* player,int trap);
	void Board::GenerateByBinaryTree();
	Board::~Board();
	void Board::removeItem(int row, int colum);
	void Board::addItem(int row, int colum);
	void Board::moveCharcter(int y0, int x0, int y1, int x1);
	void Board::moveItem(Item* item, int toRow, int toColum);
	int Board::check(int y, int x);
	void Board::keyPressEvent(QKeyEvent* event);

	void Board::shuffleArray(int* array, int size);
	void Board::RecursiveBackTraing(int y, int x);
	int Board::inRange(int y, int x);

	void Make_Trap();
	int rand(int a, int b);
};