#pragma once

#include <string>
#include <QtWidgets/QgraphicsPixmapItem>

class Item : public QGraphicsPixmapItem {
public:
	Item(const std::string& path, int row, int colum, QGraphicsItem* parent);
	std::string path() const;		//위치 반환
	int row() const;
	int colum() const;

	void setRow(int row);
	void setColum(int colum);

private:
	const std::string _path;		// 사진 위치
	int _row;
	int _colum;
};