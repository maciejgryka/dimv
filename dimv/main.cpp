#include "dimv.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	dimv w;
	w.show();
	return a.exec();
}
