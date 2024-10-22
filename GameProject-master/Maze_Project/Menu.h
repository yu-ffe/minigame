#pragma once

#include <QtWidgets/qgraphicsScene>
//#include <QtWidgets/QgraphicsRectItem>
#include <QtWidgets/QGraphicsTextItem>
#include <QtWidgets/qpushbutton.h>
#include <qgraphicsview.h>
#include <qlineedit.h>
#include <qlabel.h>

#include "Player.h"
#include "Board.h"
#include "Consts.h"

class Menu : public QGraphicsScene {
	Q_OBJECT
private:
	int _size;
	Player* _player;
	QGraphicsView* _view;
	Board* board;

public:
	Menu(QGraphicsView* view);
	void show();
	void Windows_setting(int widht, int height);
	void add_Widget();

private slots:
	void btn_click();

private:
	QLineEdit _Level_INPUT;
	QLineEdit _NAME_INPUT;
	QLabel _Level_LABEL;
	QLabel _NAME_LABEL;
	QPushButton _button;
};