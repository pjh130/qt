/********************************************************************************
** Form generated from reading UI file 'frmsavelog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMSAVELOG_H
#define UI_FRMSAVELOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_frmSaveLog
{
public:
    QGridLayout *gridLayout;
    QCheckBox *ckTimer;
    QCheckBox *ckSave;
    QPushButton *btnDebug;
    QTextEdit *txtMain;
    QCheckBox *ckNet;

    void setupUi(QWidget *frmSaveLog)
    {
        if (frmSaveLog->objectName().isEmpty())
            frmSaveLog->setObjectName(QStringLiteral("frmSaveLog"));
        frmSaveLog->resize(400, 300);
        gridLayout = new QGridLayout(frmSaveLog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        ckTimer = new QCheckBox(frmSaveLog);
        ckTimer->setObjectName(QStringLiteral("ckTimer"));

        gridLayout->addWidget(ckTimer, 1, 1, 1, 1);

        ckSave = new QCheckBox(frmSaveLog);
        ckSave->setObjectName(QStringLiteral("ckSave"));

        gridLayout->addWidget(ckSave, 1, 3, 1, 1);

        btnDebug = new QPushButton(frmSaveLog);
        btnDebug->setObjectName(QStringLiteral("btnDebug"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btnDebug->sizePolicy().hasHeightForWidth());
        btnDebug->setSizePolicy(sizePolicy);

        gridLayout->addWidget(btnDebug, 1, 0, 1, 1);

        txtMain = new QTextEdit(frmSaveLog);
        txtMain->setObjectName(QStringLiteral("txtMain"));

        gridLayout->addWidget(txtMain, 0, 0, 1, 4);

        ckNet = new QCheckBox(frmSaveLog);
        ckNet->setObjectName(QStringLiteral("ckNet"));

        gridLayout->addWidget(ckNet, 1, 2, 1, 1);


        retranslateUi(frmSaveLog);

        QMetaObject::connectSlotsByName(frmSaveLog);
    } // setupUi

    void retranslateUi(QWidget *frmSaveLog)
    {
        frmSaveLog->setWindowTitle(QApplication::translate("frmSaveLog", "Form", 0));
        ckTimer->setText(QApplication::translate("frmSaveLog", "\345\256\232\346\227\266\345\231\250\346\211\223\345\215\260\346\266\210\346\201\257", 0));
        ckSave->setText(QApplication::translate("frmSaveLog", "\344\277\235\345\255\230\346\227\245\345\277\227", 0));
        btnDebug->setText(QApplication::translate("frmSaveLog", "\346\211\213\345\212\250\346\217\222\345\205\245\346\266\210\346\201\257", 0));
        ckNet->setText(QApplication::translate("frmSaveLog", "\351\207\215\345\256\232\345\220\221\345\210\260\347\275\221\347\273\234", 0));
    } // retranslateUi

};

namespace Ui {
    class frmSaveLog: public Ui_frmSaveLog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMSAVELOG_H
