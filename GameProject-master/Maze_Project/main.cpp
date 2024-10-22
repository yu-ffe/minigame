#include "Menu.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/qgraphicsScene>

int main(int argc, char* argv[]) {
	QApplication a(argc, argv);

	QGraphicsView view;
	Menu menu(&view);

	return a.exec();
}