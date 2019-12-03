/********************************************************************************
** Form generated from reading UI file 'jisuanqi7.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_JISUANQI7_H
#define UI_JISUANQI7_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_jisuanqi7Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *jisuanqi7Class)
    {
        if (jisuanqi7Class->objectName().isEmpty())
            jisuanqi7Class->setObjectName(QStringLiteral("jisuanqi7Class"));
        jisuanqi7Class->resize(600, 400);
        menuBar = new QMenuBar(jisuanqi7Class);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        jisuanqi7Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(jisuanqi7Class);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        jisuanqi7Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(jisuanqi7Class);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        jisuanqi7Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(jisuanqi7Class);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        jisuanqi7Class->setStatusBar(statusBar);

        retranslateUi(jisuanqi7Class);

        QMetaObject::connectSlotsByName(jisuanqi7Class);
    } // setupUi

    void retranslateUi(QMainWindow *jisuanqi7Class)
    {
        jisuanqi7Class->setWindowTitle(QApplication::translate("jisuanqi7Class", "jisuanqi7", nullptr));
    } // retranslateUi

};

namespace Ui {
    class jisuanqi7Class: public Ui_jisuanqi7Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_JISUANQI7_H
