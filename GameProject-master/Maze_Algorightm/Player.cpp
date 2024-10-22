#include "Player.h"

Player::Player(int x, int y, std::string name)
	: _x(x)
	, _y(y)
	, _name(name)
{
}

int Player::X()
{
	return _x;
}

int Player::Y()
{
	return _y;
}

void Player::set_X(int x)
{
    _x = x;
}

void Player::set_Y(int y)
{
    _y = y;
}
