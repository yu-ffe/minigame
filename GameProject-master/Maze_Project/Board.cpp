#include "Board.h"
#include "Consts.h"
#include <random>
#include <qdebug.h>
#include <QKeyEvent>

Board::Board(int size, Player* player, int trap)
	: _size(size)					//후에 사이즈 추가
	, _player(player)
	, _board(new Node* [size])
	, _trap(trap)
{
	QGraphicsScene::addItem(&_root);
	//_root.setX(QGraphicsScene::sceneRect().width() / 2 - (Consts::BOARD_IMAGE_SIZE * _size / 2));		//X좌표 설정
	//_root.setY(QGraphicsScene::sceneRect().height() / 2 - (Consts::BOARD_IMAGE_SIZE * _size / 2));		//Y좌표 설정
	
	if (_size % 2 == 0)
		return;
	for (int i = 0; i < _size; i++) {
		_board[i] = new Node[_size];
	}
	GenerateByBinaryTree();
	for (int row = 0; row < _size; ++row) {
		std::vector<Item*> rowItems(_size);
		_items.push_back(rowItems);
		for (int colum = 0; colum < _size; ++colum) {
			addItem(row, colum);
		}
	}
	Make_Trap();
}

void Board::GenerateByBinaryTree()
{
	//초기맵 설정
	for (int y = 0; y < _size; y++) {

		for (int x = 0; x < _size; x++) {
			if (x % 2 == 0 || y % 2 == 0) {
				_board[y][x].type = TileType::Wall;
			}
			else {
				_board[y][x].type = TileType::Empty;
				_board[y][x].came = false;
			}
		}
	}
	RecursiveBackTraing(1, 1);
	_board[1][1].type = TileType::USER;
	_board[_size - 2][_size - 1].type = TileType::Empty;
}

void Board::shuffleArray(int* array, int size) {
	int i, r, temp;
	for (i = 0; i < (size - 1); ++i)
	{
		r = i + (rand(0,4) % (size - i));
		temp = array[i];
		array[i] = array[r];
		array[r] = temp;
	}
}
void Board::RecursiveBackTraing(int y, int x) {
	int r, nx, ny;
	int directions[4] = {
			Direction::UP,
			Direction::DOWN,
			Direction::LEFT,
			Direction::RIGHT
	};
	_board[y][x].came = true;
	shuffleArray(directions, 4);

	for (r = 0; r < 4; r++) {
		nx = x + DIR[directions[r]][0];
		ny = y + DIR[directions[r]][1];

		if (inRange(ny, nx) && (_board[ny][nx].type == TileType::Empty) && !_board[ny][nx].came) {
			std::cout << "start : " << nx << " : " << ny << std::endl;
			RecursiveBackTraing(ny, nx);
			if (ny != y) {
				_board[(ny + y) / 2][nx].type = TileType::Empty;
			}
			else {
				_board[ny][(nx + x) / 2].type = TileType::Empty;
			}
		}
	}
}
int Board::inRange(int y, int x)
{
	return (y > 0 && y < _size - 1) && (x > 0 && x < _size - 1);
}
Board::~Board()
{
	for (int row = 0; row < _items.size(); ++row) {
		for (int colum = 0; colum < _items[row].size(); ++colum) {
			removeItem(row, colum);
		}
	}
	for (int i = 0; i < _size; i++) {
		delete _board[i];
	}
	delete _board;
}
void Board::Make_Trap() {
	int x, y;
	while (_trap > 0) {
		x = rand(2, _size - 2);
		y = rand(2, _size - 2);
		if (_board[y][x].type == TileType::Empty) {
			if (check(y - 1, x) == 2)
				continue;
			else if (check(y + 1, x) == 2)
				continue;
			else if (check(y, x - 1) == 2)
				continue;
			else if (check(y, x + 1) == 2)
				continue;
			else {
				_board[y][x].type = TileType::Trap;
				removeItem(y, x);
				addItem(y, x);
				_trap--;
			}
		}
	}
}
void Board::removeItem(int row, int colum)
{
	auto* item = _items[row][colum];
	if (item == nullptr)
		return;

	_items[row][colum] = nullptr;
	item->setParentItem(nullptr);
	QGraphicsScene::removeItem(item);

	delete item;
}

void Board::addItem(int row, int colum)
{
	const std::string& path_wall = Consts::paths[0].c_str();
	const std::string& path_empty = Consts::paths[1].c_str();
	const std::string& path_user = Consts::paths[2].c_str();
	const std::string& path_trap = Consts::paths[3].c_str();

	Item* item;
	if (_board[row][colum].type == TileType::Wall)
		item = new Item(path_wall, row, colum, &_root);
	else if (_board[row][colum].type == TileType::USER)
		item = new Item(path_user, row, colum, &_root);
	else if (_board[row][colum].type == TileType::Empty)
		item = new Item(path_empty, row, colum, &_root);
	else
		item = new Item(path_trap, row, colum, &_root);

	item->setPos(colum * Consts::BOARD_IMAGE_SIZE, row * Consts::BOARD_IMAGE_SIZE);
	QGraphicsScene::addItem(item);					//이름이 같지만 Scene의 addItem 함수임.
	_items[row][colum] = item;
}
int Board::rand(int a, int b) {
	std::random_device rd;

	// random_device 를 통해 난수 생성 엔진을 초기화 한다.
	std::mt19937 gen(rd());

	// 0 부터 99 까지 균등하게 나타나는 난수열을 생성하기 위해 균등 분포 정의.
	std::uniform_int_distribution<int> dis(a, b);

	return dis(gen);
}
void Board::moveCharcter(int y0, int x0, int y1, int x1)
{
	if (check(y1, x1) == 2) {
		_board[y1][x1].type = TileType::Empty;
		removeItem(y1, x1);
		addItem(y1, x1);
		
		while (true) {
			y1 = rand(2, _size - 2);
			x1 = rand(2, _size - 2);
			if (_board[y1][x1].type == TileType::Empty)
				break;
		}
	}
	
	Item* item0 = _items[y0][x0];
	Item* item1 = _items[y1][x1];

	moveItem(item0, y1, x1);
	moveItem(item1, y0, x0);

	_items[y0][x0] = item1;
	_items[y1][x1] = item0;

	Node tmp = _board[y0][x0];
	_board[y0][x0] = _board[y1][x1];
	_board[y1][x1] = tmp;

	_player->set_X(x1);
	_player->set_Y(y1);
}

void Board::moveItem(Item* item, int toRow, int toColum)
{
	item->setRow(toRow);
	item->setColum(toColum);
	item->setPos(toColum * Consts::BOARD_IMAGE_SIZE, toRow * Consts::BOARD_IMAGE_SIZE);

	_items[toRow][toColum] = item;
}

int Board::check(int y, int x) {
	if (TileType::Empty == _board[y][x].type)
		return 1;
	else if (TileType::Trap == _board[y][x].type)
		return 2;
	else
		return 0;
}

void Board::keyPressEvent(QKeyEvent* event) {
	qDebug() << "Good Working";
	auto x = _player->X();
	auto y = _player->Y();
	switch (event->key()) {
	case Qt::Key_Up:
		if (check(y - 1, x))
			moveCharcter(y, x, y - 1, x);
		break;
	case Qt::Key_Down:
		if (check(y + 1, x))
			moveCharcter(y, x, y + 1, x);
		break;
	case Qt::Key_Left:
		if (check(y, x - 1))
			moveCharcter(y, x, y, x - 1);
		break;
	case Qt::Key_Right:
		if (check(y, x + 1))
			moveCharcter(y, x, y, x + 1);
		break;
	}
	if (_board[_size - 2][_size - 1].type == TileType::USER)
		return;
}