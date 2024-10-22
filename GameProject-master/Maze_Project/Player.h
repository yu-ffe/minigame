#pragma once
#include<conio.h>
#include<iostream>
#include <qstring.h>

class Player {
private:
	int _x;
	int _y;
	QString _name;
public:
	Player(int x, int y, QString name);
	int X() const;
	int Y() const;
	void set_X(int x);
	void set_Y(int y);
	void set_Name(const QString name);
};