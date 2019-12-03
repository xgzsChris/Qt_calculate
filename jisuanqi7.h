#pragma once

#include <QtWidgets/QMainWindow>
#include "jisuanqi7.h"
#include <QWidget>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLineEdit>
#include <QToolButton>
#include <QTableWidget>
#include <QPalette>
#include <QColor>
#include <QStack>
#include <QHeaderView>
class MainWindow : public QMainWindow
{
	Q_OBJECT
private:
	QWidget * widget;
	QVBoxLayout *mainLayout;
	QVBoxLayout *leftLayout;
	QGridLayout *rightLayout;
	QHBoxLayout *bottomLayout;
	QLineEdit *lineEdit;
	QToolButton *digitButtons[10];                  //数字按钮
	QToolButton *symbolButtons[10];                 //运算符按钮
	QStringList stackChange;
	bool pointnumber = 0;
	bool flag;
	bool buttonFlag;
	void initUI();
	QToolButton *createButtons(const QString &text);
	void calculate();
private slots:
	void buttonClicked();
public:
	MainWindow(QWidget *parent = 0);
};

