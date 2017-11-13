#include "ApplicationSwitcher.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ApplicationSwitcher w;
	w.showFullScreen();
	return a.exec();
}
