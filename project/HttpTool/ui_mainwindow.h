/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QColumnView>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_4;
    QGroupBox *groupBoxReq;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEditUrl;
    QHBoxLayout *horizontalLayout_2;
    QComboBox *comboBox;
    QPushButton *pushButtonSubmit;
    QSpacerItem *horizontalSpacer;
    QTabWidget *tabWidget;
    QWidget *Content;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_3;
    QRadioButton *radioButtonContent;
    QRadioButton *radioButtonFile;
    QLineEdit *lineEditFile;
    QPushButton *pushButtonFile;
    QTextEdit *textEditResquest;
    QWidget *tabHeaders;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_9;
    QPushButton *pushButtonHeader;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer_2;
    QWidget *tabParameters;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *pushButtonParaAdd;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer;
    QGroupBox *groupBoxResponse;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_2;
    QLabel *labelMethod;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_3;
    QLabel *labelUrl;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_4;
    QLabel *labelStatus;
    QTextEdit *textEditResponse;
    QGroupBox *groupBoxHistory;
    QVBoxLayout *verticalLayout_2;
    QColumnView *columnView;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1014, 640);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_3 = new QVBoxLayout(centralWidget);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        groupBoxReq = new QGroupBox(centralWidget);
        groupBoxReq->setObjectName(QStringLiteral("groupBoxReq"));
        verticalLayout = new QVBoxLayout(groupBoxReq);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(9, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(groupBoxReq);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);

        horizontalLayout->addWidget(label);

        lineEditUrl = new QLineEdit(groupBoxReq);
        lineEditUrl->setObjectName(QStringLiteral("lineEditUrl"));

        horizontalLayout->addWidget(lineEditUrl);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        comboBox = new QComboBox(groupBoxReq);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        horizontalLayout_2->addWidget(comboBox);

        pushButtonSubmit = new QPushButton(groupBoxReq);
        pushButtonSubmit->setObjectName(QStringLiteral("pushButtonSubmit"));

        horizontalLayout_2->addWidget(pushButtonSubmit);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_2);

        tabWidget = new QTabWidget(groupBoxReq);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        Content = new QWidget();
        Content->setObjectName(QStringLiteral("Content"));
        verticalLayout_5 = new QVBoxLayout(Content);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(-1, 0, -1, 0);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        radioButtonContent = new QRadioButton(Content);
        radioButtonContent->setObjectName(QStringLiteral("radioButtonContent"));
        radioButtonContent->setChecked(true);

        horizontalLayout_3->addWidget(radioButtonContent);

        radioButtonFile = new QRadioButton(Content);
        radioButtonFile->setObjectName(QStringLiteral("radioButtonFile"));

        horizontalLayout_3->addWidget(radioButtonFile);

        lineEditFile = new QLineEdit(Content);
        lineEditFile->setObjectName(QStringLiteral("lineEditFile"));

        horizontalLayout_3->addWidget(lineEditFile);

        pushButtonFile = new QPushButton(Content);
        pushButtonFile->setObjectName(QStringLiteral("pushButtonFile"));

        horizontalLayout_3->addWidget(pushButtonFile);


        verticalLayout_5->addLayout(horizontalLayout_3);

        textEditResquest = new QTextEdit(Content);
        textEditResquest->setObjectName(QStringLiteral("textEditResquest"));

        verticalLayout_5->addWidget(textEditResquest);

        tabWidget->addTab(Content, QString());
        tabHeaders = new QWidget();
        tabHeaders->setObjectName(QStringLiteral("tabHeaders"));
        verticalLayout_7 = new QVBoxLayout(tabHeaders);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        pushButtonHeader = new QPushButton(tabHeaders);
        pushButtonHeader->setObjectName(QStringLiteral("pushButtonHeader"));

        horizontalLayout_9->addWidget(pushButtonHeader);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_3);


        verticalLayout_7->addLayout(horizontalLayout_9);

        verticalSpacer_2 = new QSpacerItem(20, 292, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_7->addItem(verticalSpacer_2);

        tabWidget->addTab(tabHeaders, QString());
        tabParameters = new QWidget();
        tabParameters->setObjectName(QStringLiteral("tabParameters"));
        verticalLayout_6 = new QVBoxLayout(tabParameters);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        pushButtonParaAdd = new QPushButton(tabParameters);
        pushButtonParaAdd->setObjectName(QStringLiteral("pushButtonParaAdd"));

        horizontalLayout_8->addWidget(pushButtonParaAdd);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_2);


        verticalLayout_6->addLayout(horizontalLayout_8);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer);

        tabWidget->addTab(tabParameters, QString());

        verticalLayout->addWidget(tabWidget);


        horizontalLayout_4->addWidget(groupBoxReq);

        groupBoxResponse = new QGroupBox(centralWidget);
        groupBoxResponse->setObjectName(QStringLiteral("groupBoxResponse"));
        verticalLayout_4 = new QVBoxLayout(groupBoxResponse);
        verticalLayout_4->setSpacing(10);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(9, 0, 0, 0);
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_2 = new QLabel(groupBoxResponse);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font);
        label_2->setTextFormat(Qt::RichText);

        horizontalLayout_5->addWidget(label_2);

        labelMethod = new QLabel(groupBoxResponse);
        labelMethod->setObjectName(QStringLiteral("labelMethod"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(labelMethod->sizePolicy().hasHeightForWidth());
        labelMethod->setSizePolicy(sizePolicy);

        horizontalLayout_5->addWidget(labelMethod);


        verticalLayout_4->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_3 = new QLabel(groupBoxResponse);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFont(font);

        horizontalLayout_6->addWidget(label_3);

        labelUrl = new QLabel(groupBoxResponse);
        labelUrl->setObjectName(QStringLiteral("labelUrl"));
        sizePolicy.setHeightForWidth(labelUrl->sizePolicy().hasHeightForWidth());
        labelUrl->setSizePolicy(sizePolicy);

        horizontalLayout_6->addWidget(labelUrl);


        verticalLayout_4->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_4 = new QLabel(groupBoxResponse);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setFont(font);

        horizontalLayout_7->addWidget(label_4);

        labelStatus = new QLabel(groupBoxResponse);
        labelStatus->setObjectName(QStringLiteral("labelStatus"));
        sizePolicy.setHeightForWidth(labelStatus->sizePolicy().hasHeightForWidth());
        labelStatus->setSizePolicy(sizePolicy);

        horizontalLayout_7->addWidget(labelStatus);


        verticalLayout_4->addLayout(horizontalLayout_7);

        textEditResponse = new QTextEdit(groupBoxResponse);
        textEditResponse->setObjectName(QStringLiteral("textEditResponse"));

        verticalLayout_4->addWidget(textEditResponse);


        horizontalLayout_4->addWidget(groupBoxResponse);

        horizontalLayout_4->setStretch(0, 5);
        horizontalLayout_4->setStretch(1, 5);

        verticalLayout_3->addLayout(horizontalLayout_4);

        groupBoxHistory = new QGroupBox(centralWidget);
        groupBoxHistory->setObjectName(QStringLiteral("groupBoxHistory"));
        verticalLayout_2 = new QVBoxLayout(groupBoxHistory);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        columnView = new QColumnView(groupBoxHistory);
        columnView->setObjectName(QStringLiteral("columnView"));
        columnView->setStyleSheet(QStringLiteral(""));
        columnView->setResizeGripsVisible(true);

        verticalLayout_2->addWidget(columnView);


        verticalLayout_3->addWidget(groupBoxHistory);

        verticalLayout_3->setStretch(0, 7);
        verticalLayout_3->setStretch(1, 3);
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "HttpTool", 0));
        groupBoxReq->setTitle(QApplication::translate("MainWindow", "Request", 0));
        label->setText(QApplication::translate("MainWindow", "URL ", 0));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "GET", 0)
         << QApplication::translate("MainWindow", "POST", 0)
         << QApplication::translate("MainWindow", "PUT", 0)
         << QApplication::translate("MainWindow", "DELETE", 0)
         << QApplication::translate("MainWindow", "PATCH", 0)
         << QApplication::translate("MainWindow", "OPTIONS", 0)
         << QApplication::translate("MainWindow", "HEAD", 0)
         << QApplication::translate("MainWindow", "TRACE", 0)
         << QApplication::translate("MainWindow", "CONNECT", 0)
        );
        pushButtonSubmit->setText(QApplication::translate("MainWindow", "Submit", 0));
        radioButtonContent->setText(QApplication::translate("MainWindow", "Content", 0));
        radioButtonFile->setText(QApplication::translate("MainWindow", "File", 0));
        pushButtonFile->setText(QApplication::translate("MainWindow", "Browser", 0));
        tabWidget->setTabText(tabWidget->indexOf(Content), QApplication::translate("MainWindow", "Content to send", 0));
        pushButtonHeader->setText(QApplication::translate("MainWindow", "\345\242\236\345\212\240\345\217\202\346\225\260", 0));
        tabWidget->setTabText(tabWidget->indexOf(tabHeaders), QApplication::translate("MainWindow", "Headers", 0));
        pushButtonParaAdd->setText(QApplication::translate("MainWindow", "\345\242\236\345\212\240\345\217\202\346\225\260", 0));
        tabWidget->setTabText(tabWidget->indexOf(tabParameters), QApplication::translate("MainWindow", "Parameters", 0));
        groupBoxResponse->setTitle(QApplication::translate("MainWindow", "Response", 0));
        label_2->setText(QApplication::translate("MainWindow", "Method: ", 0));
        labelMethod->setText(QApplication::translate("MainWindow", "GET", 0));
        label_3->setText(QApplication::translate("MainWindow", "Url: ", 0));
        labelUrl->setText(QApplication::translate("MainWindow", "http://example.com", 0));
        label_4->setText(QApplication::translate("MainWindow", "Status\357\274\232 ", 0));
        labelStatus->setText(QApplication::translate("MainWindow", "200 OK", 0));
        groupBoxHistory->setTitle(QApplication::translate("MainWindow", "History", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
