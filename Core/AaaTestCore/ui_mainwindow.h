/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
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
    QPushButton *pushButton_ScreenShot;
    QPushButton *pushButton_qxtglobalshortcut;
    QPushButton *pushButton_sql;
    QPushButton *pushButton_file;
    QPushButton *pushButton_time;
    QPushButton *pushButton_os;
    QPushButton *pushButton_string;
    QPushButton *pushButton_settings;
    QPushButton *pushButton_image;
    QPushButton *pushButton_textcodec;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(400, 488);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        pushButton_email = new QPushButton(centralWidget);
        pushButton_email->setObjectName(QString::fromUtf8("pushButton_email"));

        verticalLayout->addWidget(pushButton_email);

        pushButton_excel = new QPushButton(centralWidget);
        pushButton_excel->setObjectName(QString::fromUtf8("pushButton_excel"));

        verticalLayout->addWidget(pushButton_excel);

        pushButton_log = new QPushButton(centralWidget);
        pushButton_log->setObjectName(QString::fromUtf8("pushButton_log"));

        verticalLayout->addWidget(pushButton_log);

        pushButton_network = new QPushButton(centralWidget);
        pushButton_network->setObjectName(QString::fromUtf8("pushButton_network"));

        verticalLayout->addWidget(pushButton_network);

        pushButton_zip = new QPushButton(centralWidget);
        pushButton_zip->setObjectName(QString::fromUtf8("pushButton_zip"));

        verticalLayout->addWidget(pushButton_zip);

        pushButton_thread = new QPushButton(centralWidget);
        pushButton_thread->setObjectName(QString::fromUtf8("pushButton_thread"));

        verticalLayout->addWidget(pushButton_thread);

        pushButton_ScreenShot = new QPushButton(centralWidget);
        pushButton_ScreenShot->setObjectName(QString::fromUtf8("pushButton_ScreenShot"));

        verticalLayout->addWidget(pushButton_ScreenShot);

        pushButton_qxtglobalshortcut = new QPushButton(centralWidget);
        pushButton_qxtglobalshortcut->setObjectName(QString::fromUtf8("pushButton_qxtglobalshortcut"));

        verticalLayout->addWidget(pushButton_qxtglobalshortcut);

        pushButton_sql = new QPushButton(centralWidget);
        pushButton_sql->setObjectName(QString::fromUtf8("pushButton_sql"));

        verticalLayout->addWidget(pushButton_sql);

        pushButton_file = new QPushButton(centralWidget);
        pushButton_file->setObjectName(QString::fromUtf8("pushButton_file"));

        verticalLayout->addWidget(pushButton_file);

        pushButton_time = new QPushButton(centralWidget);
        pushButton_time->setObjectName(QString::fromUtf8("pushButton_time"));

        verticalLayout->addWidget(pushButton_time);

        pushButton_os = new QPushButton(centralWidget);
        pushButton_os->setObjectName(QString::fromUtf8("pushButton_os"));

        verticalLayout->addWidget(pushButton_os);

        pushButton_string = new QPushButton(centralWidget);
        pushButton_string->setObjectName(QString::fromUtf8("pushButton_string"));

        verticalLayout->addWidget(pushButton_string);

        pushButton_settings = new QPushButton(centralWidget);
        pushButton_settings->setObjectName(QString::fromUtf8("pushButton_settings"));

        verticalLayout->addWidget(pushButton_settings);

        pushButton_image = new QPushButton(centralWidget);
        pushButton_image->setObjectName(QString::fromUtf8("pushButton_image"));

        verticalLayout->addWidget(pushButton_image);

        pushButton_textcodec = new QPushButton(centralWidget);
        pushButton_textcodec->setObjectName(QString::fromUtf8("pushButton_textcodec"));

        verticalLayout->addWidget(pushButton_textcodec);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton_email->setText(QCoreApplication::translate("MainWindow", "email", nullptr));
        pushButton_excel->setText(QCoreApplication::translate("MainWindow", "excel", nullptr));
        pushButton_log->setText(QCoreApplication::translate("MainWindow", "log", nullptr));
        pushButton_network->setText(QCoreApplication::translate("MainWindow", "network", nullptr));
        pushButton_zip->setText(QCoreApplication::translate("MainWindow", "zip", nullptr));
        pushButton_thread->setText(QCoreApplication::translate("MainWindow", "thread", nullptr));
        pushButton_ScreenShot->setText(QCoreApplication::translate("MainWindow", "CaptureScreen", nullptr));
        pushButton_qxtglobalshortcut->setText(QCoreApplication::translate("MainWindow", "qxtglobalshortcut", nullptr));
        pushButton_sql->setText(QCoreApplication::translate("MainWindow", "sql", nullptr));
        pushButton_file->setText(QCoreApplication::translate("MainWindow", "file", nullptr));
        pushButton_time->setText(QCoreApplication::translate("MainWindow", "time", nullptr));
        pushButton_os->setText(QCoreApplication::translate("MainWindow", "os", nullptr));
        pushButton_string->setText(QCoreApplication::translate("MainWindow", "string", nullptr));
        pushButton_settings->setText(QCoreApplication::translate("MainWindow", "settings", nullptr));
        pushButton_image->setText(QCoreApplication::translate("MainWindow", "image", nullptr));
        pushButton_textcodec->setText(QCoreApplication::translate("MainWindow", "textcodec", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
