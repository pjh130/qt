/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton_email;
    QPushButton *pushButton_excel;
    QPushButton *pushButton_log;
    QPushButton *pushButton_network;
    QPushButton *pushButton_zip;
    QPushButton *pushButton_thread;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(400, 338);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        pushButton_email = new QPushButton(centralWidget);
        pushButton_email->setObjectName(QStringLiteral("pushButton_email"));

        verticalLayout->addWidget(pushButton_email);

        pushButton_excel = new QPushButton(centralWidget);
        pushButton_excel->setObjectName(QStringLiteral("pushButton_excel"));

        verticalLayout->addWidget(pushButton_excel);

        pushButton_log = new QPushButton(centralWidget);
        pushButton_log->setObjectName(QStringLiteral("pushButton_log"));

        verticalLayout->addWidget(pushButton_log);

        pushButton_network = new QPushButton(centralWidget);
        pushButton_network->setObjectName(QStringLiteral("pushButton_network"));

        verticalLayout->addWidget(pushButton_network);

        pushButton_zip = new QPushButton(centralWidget);
        pushButton_zip->setObjectName(QStringLiteral("pushButton_zip"));

        verticalLayout->addWidget(pushButton_zip);

        pushButton_thread = new QPushButton(centralWidget);
        pushButton_thread->setObjectName(QStringLiteral("pushButton_thread"));

        verticalLayout->addWidget(pushButton_thread);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 17));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        pushButton_email->setText(QApplication::translate("MainWindow", "email", 0));
        pushButton_excel->setText(QApplication::translate("MainWindow", "excel", 0));
        pushButton_log->setText(QApplication::translate("MainWindow", "log", 0));
        pushButton_network->setText(QApplication::translate("MainWindow", "network", 0));
        pushButton_zip->setText(QApplication::translate("MainWindow", "zip", 0));
        pushButton_thread->setText(QApplication::translate("MainWindow", "thread", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
