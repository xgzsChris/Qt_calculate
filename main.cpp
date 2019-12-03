#include "jisuanqi7.h"
#include <QApplication>
#include <QDesktopWidget>
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	w.setFixedHeight(550);                //设置窗口高度为550
	w.setFixedWidth(450);                 //设置窗口宽度为450
	w.show();
	return a.exec();
}