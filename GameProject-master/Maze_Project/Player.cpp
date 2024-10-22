#include "Player.h"

Player::Player(int x, int y, QString name)
	: _x(x)
	, _y(y)
	, _name(name)
{
}

int Player::X() const
{
	return _x;
}

int Player::Y() const
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

void Player::set_Name(const QString name) {
	_name = name;
}