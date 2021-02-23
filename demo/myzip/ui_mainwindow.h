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
#include <QtWidgets/QHBoxLayout>
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
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_file;
    QPushButton *pushButton_file_extract;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_files;
    QPushButton *pushButton_files_extract;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_dir;
    QPushButton *pushButton_dir_extract;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(471, 307);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButton_file = new QPushButton(centralWidget);
        pushButton_file->setObjectName(QStringLiteral("pushButton_file"));

        horizontalLayout->addWidget(pushButton_file);

        pushButton_file_extract = new QPushButton(centralWidget);
        pushButton_file_extract->setObjectName(QStringLiteral("pushButton_file_extract"));

        horizontalLayout->addWidget(pushButton_file_extract);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        pushButton_files = new QPushButton(centralWidget);
        pushButton_files->setObjectName(QStringLiteral("pushButton_files"));

        horizontalLayout_2->addWidget(pushButton_files);

        pushButton_files_extract = new QPushButton(centralWidget);
        pushButton_files_extract->setObjectName(QStringLiteral("pushButton_files_extract"));

        horizontalLayout_2->addWidget(pushButton_files_extract);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        pushButton_dir = new QPushButton(centralWidget);
        pushButton_dir->setObjectName(QStringLiteral("pushButton_dir"));

        horizontalLayout_3->addWidget(pushButton_dir);

        pushButton_dir_extract = new QPushButton(centralWidget);
        pushButton_dir_extract->setObjectName(QStringLiteral("pushButton_dir_extract"));

        horizontalLayout_3->addWidget(pushButton_dir_extract);


        verticalLayout->addLayout(horizontalLayout_3);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 471, 17));
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
        pushButton_file->setText(QApplication::translate("MainWindow", "\345\216\213\347\274\251\345\215\225\344\270\252\346\226\207\344\273\266", 0));
        pushButton_file_extract->setText(QApplication::translate("MainWindow", "\350\247\243\345\216\213\345\215\225\344\270\252\346\226\207\344\273\266", 0));
        pushButton_files->setText(QApplication::translate("MainWindow", "\345\216\213\347\274\251\345\244\232\344\270\252\346\226\207\344\273\266", 0));
        pushButton_files_extract->setText(QApplication::translate("MainWindow", "\350\247\243\345\216\213\345\244\232\344\270\252\346\226\207\344\273\266", 0));
        pushButton_dir->setText(QApplication::translate("MainWindow", "\345\216\213\347\274\251\346\226\207\344\273\266\345\244\271", 0));
        pushButton_dir_extract->setText(QApplication::translate("MainWindow", "\350\247\243\345\216\213\346\226\207\344\273\266\345\244\271", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
