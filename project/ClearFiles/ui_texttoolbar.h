/********************************************************************************
** Form generated from reading UI file 'texttoolbar.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEXTTOOLBAR_H
#define UI_TEXTTOOLBAR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>
#include "toolbarcommon.h"

QT_BEGIN_NAMESPACE

class Ui_TextToolBar
{
public:
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *comboBox;
    ToolbarCommon *widget;

    void setupUi(QWidget *TextToolBar)
    {
        if (TextToolBar->objectName().isEmpty())
            TextToolBar->setObjectName(QString::fromUtf8("TextToolBar"));
        TextToolBar->resize(260, 40);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(TextToolBar->sizePolicy().hasHeightForWidth());
        TextToolBar->setSizePolicy(sizePolicy);
        TextToolBar->setMinimumSize(QSize(260, 40));
        TextToolBar->setMaximumSize(QSize(260, 40));
        TextToolBar->setAutoFillBackground(true);
        horizontalLayout = new QHBoxLayout(TextToolBar);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(1, 1, 1, 1);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetFixedSize);
        label = new QLabel(TextToolBar);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(32, 32));
        label->setMaximumSize(QSize(32, 32));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font.setPointSize(14);
        font.setBold(true);
        font.setItalic(false);
        font.setWeight(75);
        font.setKerning(false);
        label->setFont(font);
        label->setAutoFillBackground(true);
        label->setPixmap(QPixmap(QString::fromUtf8(":/Text.png")));
        label->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label);

        comboBox = new QComboBox(TextToolBar);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setMinimumSize(QSize(65, 21));
        comboBox->setMaximumSize(QSize(65, 21));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font1.setPointSize(12);
        comboBox->setFont(font1);
        comboBox->setFocusPolicy(Qt::NoFocus);
        comboBox->setAutoFillBackground(true);
        comboBox->setFrame(false);

        horizontalLayout->addWidget(comboBox);

        widget = new ToolbarCommon(TextToolBar);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMinimumSize(QSize(176, 32));
        widget->setMaximumSize(QSize(176, 32));

        horizontalLayout->addWidget(widget);


        retranslateUi(TextToolBar);

        QMetaObject::connectSlotsByName(TextToolBar);
    } // setupUi

    void retranslateUi(QWidget *TextToolBar)
    {
        TextToolBar->setWindowTitle(QCoreApplication::translate("TextToolBar", "Form", nullptr));
        label->setText(QString());
        comboBox->setItemText(0, QCoreApplication::translate("TextToolBar", "8", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("TextToolBar", "9", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("TextToolBar", "10", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("TextToolBar", "11", nullptr));
        comboBox->setItemText(4, QCoreApplication::translate("TextToolBar", "12", nullptr));
        comboBox->setItemText(5, QCoreApplication::translate("TextToolBar", "14", nullptr));
        comboBox->setItemText(6, QCoreApplication::translate("TextToolBar", "16", nullptr));
        comboBox->setItemText(7, QCoreApplication::translate("TextToolBar", "18", nullptr));
        comboBox->setItemText(8, QCoreApplication::translate("TextToolBar", "20", nullptr));

    } // retranslateUi

};

namespace Ui {
    class TextToolBar: public Ui_TextToolBar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEXTTOOLBAR_H
