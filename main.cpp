#include "jisuanqi7.h"
#include <QApplication>
#include <QDesktopWidget>
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	w.setFixedHeight(550);                //���ô��ڸ߶�Ϊ550
	w.setFixedWidth(450);                 //���ô��ڿ��Ϊ450
	w.show();
	return a.exec();
}