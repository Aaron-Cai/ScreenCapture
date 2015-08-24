/********************************************************************************
** Form generated from reading UI file 'screencapture.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCREENCAPTURE_H
#define UI_SCREENCAPTURE_H

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

class Ui_ScreenCaptureClass
{
public:
    QWidget *centralWidget;
    QStatusBar *statusBar;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *ScreenCaptureClass)
    {
        if (ScreenCaptureClass->objectName().isEmpty())
            ScreenCaptureClass->setObjectName(QStringLiteral("ScreenCaptureClass"));
        ScreenCaptureClass->resize(600, 400);
        QIcon icon;
        icon.addFile(QStringLiteral(":/ScreenCapture/scissors_2.png"), QSize(), QIcon::Normal, QIcon::Off);
        ScreenCaptureClass->setWindowIcon(icon);
        centralWidget = new QWidget(ScreenCaptureClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        ScreenCaptureClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(ScreenCaptureClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ScreenCaptureClass->setStatusBar(statusBar);
        menuBar = new QMenuBar(ScreenCaptureClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 26));
        ScreenCaptureClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ScreenCaptureClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ScreenCaptureClass->addToolBar(Qt::TopToolBarArea, mainToolBar);

        retranslateUi(ScreenCaptureClass);

        QMetaObject::connectSlotsByName(ScreenCaptureClass);
    } // setupUi

    void retranslateUi(QMainWindow *ScreenCaptureClass)
    {
        ScreenCaptureClass->setWindowTitle(QApplication::translate("ScreenCaptureClass", "ScreenCapture", 0));
    } // retranslateUi

};

namespace Ui {
    class ScreenCaptureClass: public Ui_ScreenCaptureClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCREENCAPTURE_H
