#include "Board.h"
#include "Player.h"

Board::Board(int size, Player* player)
	: _size(size)
	, _board(new Node* [size] {})
	, _player(player)
{
	if (_size % 2 == 0)
		return;
	for (int i = 0; i < size; i++) {
		_board[i] = new Node[size];
	}
	GenerateByBinaryTree();
	println(true);
}
Board::~Board()
{
	for (int i = 0; i < _size; i++) {
		delete _board[i];
	}
	delete _board;
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
	RecursiveBackTraing(1,1);
	_board[1][1].type = TileType::USER;
}

void Board::shuffleArray(int* array, int size) {
	int i, r, temp;
	for (i = 0; i < (size - 1); ++i)
	{
		r = i + (rand() % (size - i));
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
void Board::println(bool m)
{
	if (!m)
		system("cls");
	for (int y = 0; y < _size; y++) {
		for (int x = 0; x < _size; x++) {
			if (_board[y][x].type == TileType::Wall) 
				std::cout << "ㅁ";
			else if(_board[y][x].type == TileType::USER)
				std::cout << "ㅍ";
			else
				std::cout << "  ";
		}
		std::cout << std::endl;
	}
}

void Board::moveCharcter(int x0, int y0, int x1, int y1)
{
	TileType tmp = _board[y0][x0].type;
	_board[y0][x0].type = _board[y1][x1].type;
	_board[y1][x1].type = tmp;

	_player->set_X(x1);
	_player->set_Y(y1);
}
bool Board::check(int x, int y) {
	if (TileType::Empty == _board[y][x].type)
		return true;
	else
		return false;
}

void Board::PlayerMoveEvent()
{
	char c;
	int x;
	int y;
	for (;;) {
		if (_kbhit()) {        //키보드 입력 확인 (true / false)
			c = _getch();      // 방향키 입력시 224 00이 들어오게 되기에 앞에 있는 값 224를 없앰
			if (c == -32) {    // -32로 입력되면
				c = _getch();  // 새로 입력값을 판별하여 상하좌우 출력
				x = _player->X();
				y = _player->Y();
				switch (c) {
				case static_cast<int>(Player::Move::LEFT):
					if (check(x - 1, y))
						moveCharcter(x, y, x - 1, y);
					break;
				case static_cast<int>(Player::Move::RIGHT):
					if (check(x + 1, y))
						moveCharcter(x, y, x + 1, y);
					break;
				case static_cast<int>(Player::Move::DOWN):
					if (check(x, y+1))
						moveCharcter(x, y, x , y+1);
					break;
				case static_cast<int>(Player::Move::UP):
					if (check(x, y - 1))
						moveCharcter(x, y, x, y-1);
					break;
				}
			}
			println(false);
		}
	}
}

//초기맵 설정
	//for (int y = 0; y < _size; y++) {
	//	for (int x = 0; x < _size; x++) {
	//		if (x % 2 == 0 || y % 2 == 0)
	//			_board[y][x] = TileType::Wall;
	//		else
	//			_board[y][x] = TileType::Empty;
	//	}
	//}
	//srand(unsigned(time(NULL)));

	//랜덤 길 뚫기
	//for (int y = 0; y < _size; y++) {
	//	for (int x = 0; x < _size; x++) {
	//		if (x % 2 == 0 || y % 2 == 0)
	//			continue;

	//		if (y == _size - 2) {
	//			_board[y][x + 1] = TileType::Empty;
	//			continue;
	//		}
	//		if (x == _size - 2) {
	//			_board[y + 1][x] = TileType::Empty;
	//			continue;
	//		}
	//		if (rand() % 2 == 0) {
	//			_board[y][x + 1] = TileType::Empty;
	//		}
	//		else {
	//			_board[y+1][x] = TileType::Empty;
	//		}
	//	}
	//}
	//_board[_player->Y()][_player->X()] = TileType::USER;
	//println(true);