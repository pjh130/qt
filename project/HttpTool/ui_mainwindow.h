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
#include <QtWidgets/QScrollArea>
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
    QComboBox *comboBoxMethod;
    QPushButton *pushButtonSubmit;
    QSpacerItem *horizontalSpacer;
    QTabWidget *tabWidgetRequest;
    QWidget *Auth;
    QVBoxLayout *verticalLayout_10;
    QHBoxLayout *horizontalLayout_3;
    QComboBox *comboBoxAuth;
    QSpacerItem *horizontalSpacer_4;
    QScrollArea *scrollAreaAuth;
    QWidget *scrollAreaWidgetContents_3;
    QWidget *tabHeaders;
    QVBoxLayout *verticalLayout_7;
    QScrollArea *scrollAreaHeader;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayoutHeader;
    QHBoxLayout *horizontalLayout_9;
    QPushButton *pushButtonHeader;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer_2;
    QWidget *tabBody;
    QVBoxLayout *verticalLayout_13;
    QTabWidget *tabWidgetBody;
    QWidget *tabFormdata;
    QVBoxLayout *verticalLayout_9;
    QScrollArea *scrollAreaFormdata;
    QWidget *scrollAreaWidgetContents_4;
    QVBoxLayout *verticalLayoutFormdata;
    QHBoxLayout *horizontalLayoutFormdata;
    QPushButton *pushButtonAddFormdata;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *verticalSpacer_4;
    QWidget *tabXwwwForm;
    QVBoxLayout *verticalLayoutXwwFormTab;
    QScrollArea *scrollAreaXwwwForm;
    QWidget *scrollAreaWidgetContents_2;
    QVBoxLayout *verticalLayoutXwwForm;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *pushButtonAddXwww;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer;
    QWidget *tabRaw;
    QVBoxLayout *verticalLayout_5;
    QTextEdit *textEditRaw;
    QWidget *tabBinary;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_10;
    QPushButton *pushButtonBinary;
    QLineEdit *lineEditBinary;
    QSpacerItem *verticalSpacer_3;
    QGroupBox *groupBoxResponse;
    QVBoxLayout *verticalLayout_11;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_2;
    QLabel *labelMethod;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_3;
    QLabel *labelUrl;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_4;
    QLabel *labelStatus;
    QHBoxLayout *horizontalLayout_11;
    QGroupBox *groupBoxResHeaders;
    QVBoxLayout *verticalLayout_4;
    QTextEdit *textEditResponseHeaders;
    QPushButton *pushButtonCopyHeaders;
    QGroupBox *groupBoxContent;
    QVBoxLayout *verticalLayout_8;
    QTextEdit *textEditResponseContent;
    QPushButton *pushButtonCopyContent;
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
        comboBoxMethod = new QComboBox(groupBoxReq);
        comboBoxMethod->setObjectName(QStringLiteral("comboBoxMethod"));

        horizontalLayout_2->addWidget(comboBoxMethod);

        pushButtonSubmit = new QPushButton(groupBoxReq);
        pushButtonSubmit->setObjectName(QStringLiteral("pushButtonSubmit"));

        horizontalLayout_2->addWidget(pushButtonSubmit);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_2);

        tabWidgetRequest = new QTabWidget(groupBoxReq);
        tabWidgetRequest->setObjectName(QStringLiteral("tabWidgetRequest"));
        Auth = new QWidget();
        Auth->setObjectName(QStringLiteral("Auth"));
        verticalLayout_10 = new QVBoxLayout(Auth);
        verticalLayout_10->setSpacing(0);
        verticalLayout_10->setContentsMargins(11, 11, 11, 11);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        verticalLayout_10->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        comboBoxAuth = new QComboBox(Auth);
        comboBoxAuth->setObjectName(QStringLiteral("comboBoxAuth"));

        horizontalLayout_3->addWidget(comboBoxAuth);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);


        verticalLayout_10->addLayout(horizontalLayout_3);

        scrollAreaAuth = new QScrollArea(Auth);
        scrollAreaAuth->setObjectName(QStringLiteral("scrollAreaAuth"));
        scrollAreaAuth->setWidgetResizable(true);
        scrollAreaWidgetContents_3 = new QWidget();
        scrollAreaWidgetContents_3->setObjectName(QStringLiteral("scrollAreaWidgetContents_3"));
        scrollAreaWidgetContents_3->setGeometry(QRect(0, 0, 428, 320));
        scrollAreaAuth->setWidget(scrollAreaWidgetContents_3);

        verticalLayout_10->addWidget(scrollAreaAuth);

        tabWidgetRequest->addTab(Auth, QString());
        tabHeaders = new QWidget();
        tabHeaders->setObjectName(QStringLiteral("tabHeaders"));
        verticalLayout_7 = new QVBoxLayout(tabHeaders);
        verticalLayout_7->setSpacing(0);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        scrollAreaHeader = new QScrollArea(tabHeaders);
        scrollAreaHeader->setObjectName(QStringLiteral("scrollAreaHeader"));
        scrollAreaHeader->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 428, 342));
        verticalLayoutHeader = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayoutHeader->setSpacing(0);
        verticalLayoutHeader->setContentsMargins(11, 11, 11, 11);
        verticalLayoutHeader->setObjectName(QStringLiteral("verticalLayoutHeader"));
        verticalLayoutHeader->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        pushButtonHeader = new QPushButton(scrollAreaWidgetContents);
        pushButtonHeader->setObjectName(QStringLiteral("pushButtonHeader"));

        horizontalLayout_9->addWidget(pushButtonHeader);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_3);


        verticalLayoutHeader->addLayout(horizontalLayout_9);

        verticalSpacer_2 = new QSpacerItem(20, 305, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayoutHeader->addItem(verticalSpacer_2);

        scrollAreaHeader->setWidget(scrollAreaWidgetContents);

        verticalLayout_7->addWidget(scrollAreaHeader);

        tabWidgetRequest->addTab(tabHeaders, QString());
        tabBody = new QWidget();
        tabBody->setObjectName(QStringLiteral("tabBody"));
        verticalLayout_13 = new QVBoxLayout(tabBody);
        verticalLayout_13->setSpacing(0);
        verticalLayout_13->setContentsMargins(11, 11, 11, 11);
        verticalLayout_13->setObjectName(QStringLiteral("verticalLayout_13"));
        verticalLayout_13->setContentsMargins(0, 0, 0, 0);
        tabWidgetBody = new QTabWidget(tabBody);
        tabWidgetBody->setObjectName(QStringLiteral("tabWidgetBody"));
        tabFormdata = new QWidget();
        tabFormdata->setObjectName(QStringLiteral("tabFormdata"));
        verticalLayout_9 = new QVBoxLayout(tabFormdata);
        verticalLayout_9->setSpacing(0);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        verticalLayout_9->setContentsMargins(0, 0, 0, 0);
        scrollAreaFormdata = new QScrollArea(tabFormdata);
        scrollAreaFormdata->setObjectName(QStringLiteral("scrollAreaFormdata"));
        scrollAreaFormdata->setWidgetResizable(true);
        scrollAreaWidgetContents_4 = new QWidget();
        scrollAreaWidgetContents_4->setObjectName(QStringLiteral("scrollAreaWidgetContents_4"));
        scrollAreaWidgetContents_4->setGeometry(QRect(0, 0, 422, 317));
        verticalLayoutFormdata = new QVBoxLayout(scrollAreaWidgetContents_4);
        verticalLayoutFormdata->setSpacing(0);
        verticalLayoutFormdata->setContentsMargins(11, 11, 11, 11);
        verticalLayoutFormdata->setObjectName(QStringLiteral("verticalLayoutFormdata"));
        verticalLayoutFormdata->setContentsMargins(0, 0, 0, 0);
        horizontalLayoutFormdata = new QHBoxLayout();
        horizontalLayoutFormdata->setSpacing(6);
        horizontalLayoutFormdata->setObjectName(QStringLiteral("horizontalLayoutFormdata"));
        pushButtonAddFormdata = new QPushButton(scrollAreaWidgetContents_4);
        pushButtonAddFormdata->setObjectName(QStringLiteral("pushButtonAddFormdata"));

        horizontalLayoutFormdata->addWidget(pushButtonAddFormdata);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayoutFormdata->addItem(horizontalSpacer_5);


        verticalLayoutFormdata->addLayout(horizontalLayoutFormdata);

        verticalSpacer_4 = new QSpacerItem(20, 247, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayoutFormdata->addItem(verticalSpacer_4);

        scrollAreaFormdata->setWidget(scrollAreaWidgetContents_4);

        verticalLayout_9->addWidget(scrollAreaFormdata);

        tabWidgetBody->addTab(tabFormdata, QString());
        tabXwwwForm = new QWidget();
        tabXwwwForm->setObjectName(QStringLiteral("tabXwwwForm"));
        verticalLayoutXwwFormTab = new QVBoxLayout(tabXwwwForm);
        verticalLayoutXwwFormTab->setSpacing(0);
        verticalLayoutXwwFormTab->setContentsMargins(11, 11, 11, 11);
        verticalLayoutXwwFormTab->setObjectName(QStringLiteral("verticalLayoutXwwFormTab"));
        verticalLayoutXwwFormTab->setContentsMargins(0, 0, 0, 0);
        scrollAreaXwwwForm = new QScrollArea(tabXwwwForm);
        scrollAreaXwwwForm->setObjectName(QStringLiteral("scrollAreaXwwwForm"));
        scrollAreaXwwwForm->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QStringLiteral("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 101, 49));
        verticalLayoutXwwForm = new QVBoxLayout(scrollAreaWidgetContents_2);
        verticalLayoutXwwForm->setSpacing(6);
        verticalLayoutXwwForm->setContentsMargins(11, 11, 11, 11);
        verticalLayoutXwwForm->setObjectName(QStringLiteral("verticalLayoutXwwForm"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        pushButtonAddXwww = new QPushButton(scrollAreaWidgetContents_2);
        pushButtonAddXwww->setObjectName(QStringLiteral("pushButtonAddXwww"));

        horizontalLayout_8->addWidget(pushButtonAddXwww);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_2);


        verticalLayoutXwwForm->addLayout(horizontalLayout_8);

        verticalSpacer = new QSpacerItem(20, 247, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayoutXwwForm->addItem(verticalSpacer);

        scrollAreaXwwwForm->setWidget(scrollAreaWidgetContents_2);

        verticalLayoutXwwFormTab->addWidget(scrollAreaXwwwForm);

        tabWidgetBody->addTab(tabXwwwForm, QString());
        tabRaw = new QWidget();
        tabRaw->setObjectName(QStringLiteral("tabRaw"));
        verticalLayout_5 = new QVBoxLayout(tabRaw);
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        textEditRaw = new QTextEdit(tabRaw);
        textEditRaw->setObjectName(QStringLiteral("textEditRaw"));

        verticalLayout_5->addWidget(textEditRaw);

        tabWidgetBody->addTab(tabRaw, QString());
        tabBinary = new QWidget();
        tabBinary->setObjectName(QStringLiteral("tabBinary"));
        verticalLayout_6 = new QVBoxLayout(tabBinary);
        verticalLayout_6->setSpacing(0);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        pushButtonBinary = new QPushButton(tabBinary);
        pushButtonBinary->setObjectName(QStringLiteral("pushButtonBinary"));

        horizontalLayout_10->addWidget(pushButtonBinary);

        lineEditBinary = new QLineEdit(tabBinary);
        lineEditBinary->setObjectName(QStringLiteral("lineEditBinary"));

        horizontalLayout_10->addWidget(lineEditBinary);


        verticalLayout_6->addLayout(horizontalLayout_10);

        verticalSpacer_3 = new QSpacerItem(20, 249, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer_3);

        tabWidgetBody->addTab(tabBinary, QString());

        verticalLayout_13->addWidget(tabWidgetBody);

        tabWidgetRequest->addTab(tabBody, QString());

        verticalLayout->addWidget(tabWidgetRequest);


        horizontalLayout_4->addWidget(groupBoxReq);

        groupBoxResponse = new QGroupBox(centralWidget);
        groupBoxResponse->setObjectName(QStringLiteral("groupBoxResponse"));
        verticalLayout_11 = new QVBoxLayout(groupBoxResponse);
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setContentsMargins(11, 11, 11, 11);
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        verticalLayout_11->setContentsMargins(0, 0, 0, 0);
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


        verticalLayout_11->addLayout(horizontalLayout_5);

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


        verticalLayout_11->addLayout(horizontalLayout_6);

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


        verticalLayout_11->addLayout(horizontalLayout_7);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(0);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        groupBoxResHeaders = new QGroupBox(groupBoxResponse);
        groupBoxResHeaders->setObjectName(QStringLiteral("groupBoxResHeaders"));
        verticalLayout_4 = new QVBoxLayout(groupBoxResHeaders);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        textEditResponseHeaders = new QTextEdit(groupBoxResHeaders);
        textEditResponseHeaders->setObjectName(QStringLiteral("textEditResponseHeaders"));

        verticalLayout_4->addWidget(textEditResponseHeaders);

        pushButtonCopyHeaders = new QPushButton(groupBoxResHeaders);
        pushButtonCopyHeaders->setObjectName(QStringLiteral("pushButtonCopyHeaders"));

        verticalLayout_4->addWidget(pushButtonCopyHeaders);


        horizontalLayout_11->addWidget(groupBoxResHeaders);

        groupBoxContent = new QGroupBox(groupBoxResponse);
        groupBoxContent->setObjectName(QStringLiteral("groupBoxContent"));
        groupBoxContent->setCheckable(false);
        verticalLayout_8 = new QVBoxLayout(groupBoxContent);
        verticalLayout_8->setSpacing(0);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        verticalLayout_8->setContentsMargins(0, 0, 0, 0);
        textEditResponseContent = new QTextEdit(groupBoxContent);
        textEditResponseContent->setObjectName(QStringLiteral("textEditResponseContent"));

        verticalLayout_8->addWidget(textEditResponseContent);

        pushButtonCopyContent = new QPushButton(groupBoxContent);
        pushButtonCopyContent->setObjectName(QStringLiteral("pushButtonCopyContent"));

        verticalLayout_8->addWidget(pushButtonCopyContent);


        horizontalLayout_11->addWidget(groupBoxContent);


        verticalLayout_11->addLayout(horizontalLayout_11);


        horizontalLayout_4->addWidget(groupBoxResponse);

        horizontalLayout_4->setStretch(0, 4);
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

        tabWidgetRequest->setCurrentIndex(0);
        tabWidgetBody->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "HttpTool", 0));
        groupBoxReq->setTitle(QApplication::translate("MainWindow", "Request", 0));
        label->setText(QApplication::translate("MainWindow", "URL ", 0));
        lineEditUrl->setText(QApplication::translate("MainWindow", "http://localhost:60000", 0));
        comboBoxMethod->clear();
        comboBoxMethod->insertItems(0, QStringList()
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
        comboBoxAuth->clear();
        comboBoxAuth->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "No Auth", 0)
         << QApplication::translate("MainWindow", "Basic Auth", 0)
         << QApplication::translate("MainWindow", "Digest Auth", 0)
         << QApplication::translate("MainWindow", "OAuth 1.0", 0)
         << QApplication::translate("MainWindow", "OAuth 2.0", 0)
        );
        tabWidgetRequest->setTabText(tabWidgetRequest->indexOf(Auth), QApplication::translate("MainWindow", "Authorization", 0));
        pushButtonHeader->setText(QApplication::translate("MainWindow", "\345\242\236\345\212\240\345\217\202\346\225\260", 0));
        tabWidgetRequest->setTabText(tabWidgetRequest->indexOf(tabHeaders), QApplication::translate("MainWindow", "Headers", 0));
        pushButtonAddFormdata->setText(QApplication::translate("MainWindow", "\345\242\236\345\212\240\345\217\202\346\225\260", 0));
        tabWidgetBody->setTabText(tabWidgetBody->indexOf(tabFormdata), QApplication::translate("MainWindow", "form-data", 0));
        pushButtonAddXwww->setText(QApplication::translate("MainWindow", "\345\242\236\345\212\240\345\217\202\346\225\260", 0));
        tabWidgetBody->setTabText(tabWidgetBody->indexOf(tabXwwwForm), QApplication::translate("MainWindow", "x-www-form-urlencoded", 0));
        tabWidgetBody->setTabText(tabWidgetBody->indexOf(tabRaw), QApplication::translate("MainWindow", "raw", 0));
        pushButtonBinary->setText(QApplication::translate("MainWindow", "\351\200\211\346\213\251\346\226\207\344\273\266", 0));
        tabWidgetBody->setTabText(tabWidgetBody->indexOf(tabBinary), QApplication::translate("MainWindow", "binary", 0));
        tabWidgetRequest->setTabText(tabWidgetRequest->indexOf(tabBody), QApplication::translate("MainWindow", "Body", 0));
        groupBoxResponse->setTitle(QApplication::translate("MainWindow", "Response", 0));
        label_2->setText(QApplication::translate("MainWindow", "Method: ", 0));
        labelMethod->setText(QApplication::translate("MainWindow", "unknow", 0));
        label_3->setText(QApplication::translate("MainWindow", "Url: ", 0));
        labelUrl->setText(QApplication::translate("MainWindow", "unknow", 0));
        label_4->setText(QApplication::translate("MainWindow", "Status\357\274\232 ", 0));
        labelStatus->setText(QApplication::translate("MainWindow", "unknow", 0));
        groupBoxResHeaders->setTitle(QApplication::translate("MainWindow", "Headers", 0));
        pushButtonCopyHeaders->setText(QApplication::translate("MainWindow", "\345\244\215\345\210\266\345\210\260\345\211\252\350\264\264\346\235\277", 0));
        groupBoxContent->setTitle(QApplication::translate("MainWindow", "Content", 0));
        pushButtonCopyContent->setText(QApplication::translate("MainWindow", "\345\244\215\345\210\266\345\210\260\345\211\252\350\264\264\346\235\277", 0));
        groupBoxHistory->setTitle(QApplication::translate("MainWindow", "History", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
