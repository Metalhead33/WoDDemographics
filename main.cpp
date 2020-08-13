#include <QApplication>
#include <QTableWidget>
#include "MainWindow.hpp"

#include "ComboBoxItemDelegate.hpp"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return a.exec();
}
