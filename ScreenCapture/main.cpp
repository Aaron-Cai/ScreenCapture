#include "screencapture.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	a.setWindowIcon(QIcon(":/ScreenCapture/APPICON.ico"));
	ScreenCapture w;
	//w.show();
	return a.exec();
}
