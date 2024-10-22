#include "Item.h"
#include "Consts.h"

#include <QtWidgets/QGraphicsSceneMouseEvent>
#include <QtWidgets/QGraphicsItemAnimation>

Item::Item(const std::string& path, int row, int colum, QGraphicsItem* parent)
	: QGraphicsPixmapItem(QPixmap(path.c_str()).scaled(Consts::BOARD_IMAGE_SIZE, Consts::BOARD_IMAGE_SIZE), parent),
	_path(path), _row(row), _colum(colum)
{

}

std::string Item::path() const
{
	return _path;
}

int Item::row() const
{
	return _row;
}

int Item::colum() const
{
	return _colum;
}

void Item::setRow(int row)
{
	_row = row;
}

void Item::setColum(int colum)
{
	_colum = colum;
}