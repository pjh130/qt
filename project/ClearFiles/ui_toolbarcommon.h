/********************************************************************************
** Form generated from reading UI file 'toolbarcommon.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TOOLBARCOMMON_H
#define UI_TOOLBARCOMMON_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ToolbarCommon
{
public:
    QHBoxLayout *horizontalLayout;
    QLabel *title;
    QSplitter *splitter_3;
    QSplitter *splitter;
    QToolButton *toolButton_00;
    QToolButton *toolButton_01;
    QToolButton *toolButton_02;
    QToolButton *toolButton_03;
    QToolButton *toolButton_04;
    QToolButton *toolButton_05;
    QToolButton *toolButton_06;
    QToolButton *toolButton_07;
    QSplitter *splitter_2;
    QToolButton *toolButton_08;
    QToolButton *toolButton_09;
    QToolButton *toolButton_10;
    QToolButton *toolButton_11;
    QToolButton *toolButton_12;
    QToolButton *toolButton_13;
    QToolButton *toolButton_14;
    QToolButton *toolButton_15;

    void setupUi(QWidget *ToolbarCommon)
    {
        if (ToolbarCommon->objectName().isEmpty())
            ToolbarCommon->setObjectName(QString::fromUtf8("ToolbarCommon"));
        ToolbarCommon->resize(176, 40);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ToolbarCommon->sizePolicy().hasHeightForWidth());
        ToolbarCommon->setSizePolicy(sizePolicy);
        ToolbarCommon->setMinimumSize(QSize(176, 40));
        ToolbarCommon->setMaximumSize(QSize(176, 40));
        ToolbarCommon->setAutoFillBackground(true);
        horizontalLayout = new QHBoxLayout(ToolbarCommon);
        horizontalLayout->setSpacing(1);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetFixedSize);
        title = new QLabel(ToolbarCommon);
        title->setObjectName(QString::fromUtf8("title"));
        title->setMinimumSize(QSize(32, 32));
        title->setMaximumSize(QSize(32, 32));
        title->setAutoFillBackground(true);
        title->setFrameShape(QFrame::NoFrame);
        title->setFrameShadow(QFrame::Sunken);
        title->setMidLineWidth(1);
        title->setAlignment(Qt::AlignCenter);
        title->setMargin(0);
        title->setIndent(0);

        horizontalLayout->addWidget(title);

        splitter_3 = new QSplitter(ToolbarCommon);
        splitter_3->setObjectName(QString::fromUtf8("splitter_3"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(splitter_3->sizePolicy().hasHeightForWidth());
        splitter_3->setSizePolicy(sizePolicy1);
        splitter_3->setMinimumSize(QSize(135, 35));
        splitter_3->setAutoFillBackground(true);
        splitter_3->setOrientation(Qt::Vertical);
        splitter_3->setHandleWidth(1);
        splitter_3->setChildrenCollapsible(false);
        splitter = new QSplitter(splitter_3);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        sizePolicy1.setHeightForWidth(splitter->sizePolicy().hasHeightForWidth());
        splitter->setSizePolicy(sizePolicy1);
        splitter->setMinimumSize(QSize(135, 18));
        splitter->setMaximumSize(QSize(135, 16));
        splitter->setAutoFillBackground(true);
        splitter->setLineWidth(2);
        splitter->setMidLineWidth(2);
        splitter->setOrientation(Qt::Horizontal);
        splitter->setOpaqueResize(false);
        splitter->setHandleWidth(1);
        splitter->setChildrenCollapsible(false);
        toolButton_00 = new QToolButton(splitter);
        toolButton_00->setObjectName(QString::fromUtf8("toolButton_00"));
        toolButton_00->setMinimumSize(QSize(16, 16));
        toolButton_00->setMaximumSize(QSize(16, 16));
        toolButton_00->setAutoFillBackground(true);
        toolButton_00->setAutoRaise(true);
        splitter->addWidget(toolButton_00);
        toolButton_01 = new QToolButton(splitter);
        toolButton_01->setObjectName(QString::fromUtf8("toolButton_01"));
        toolButton_01->setMinimumSize(QSize(16, 16));
        toolButton_01->setMaximumSize(QSize(16, 16));
        toolButton_01->setAutoFillBackground(true);
        toolButton_01->setAutoRaise(true);
        splitter->addWidget(toolButton_01);
        toolButton_02 = new QToolButton(splitter);
        toolButton_02->setObjectName(QString::fromUtf8("toolButton_02"));
        toolButton_02->setMinimumSize(QSize(16, 16));
        toolButton_02->setMaximumSize(QSize(16, 16));
        toolButton_02->setAutoFillBackground(true);
        toolButton_02->setAutoRaise(true);
        splitter->addWidget(toolButton_02);
        toolButton_03 = new QToolButton(splitter);
        toolButton_03->setObjectName(QString::fromUtf8("toolButton_03"));
        toolButton_03->setMinimumSize(QSize(16, 16));
        toolButton_03->setMaximumSize(QSize(16, 16));
        toolButton_03->setAutoFillBackground(true);
        toolButton_03->setAutoRaise(true);
        splitter->addWidget(toolButton_03);
        toolButton_04 = new QToolButton(splitter);
        toolButton_04->setObjectName(QString::fromUtf8("toolButton_04"));
        toolButton_04->setMinimumSize(QSize(16, 16));
        toolButton_04->setMaximumSize(QSize(16, 16));
        toolButton_04->setAutoFillBackground(true);
        toolButton_04->setAutoRaise(true);
        splitter->addWidget(toolButton_04);
        toolButton_05 = new QToolButton(splitter);
        toolButton_05->setObjectName(QString::fromUtf8("toolButton_05"));
        toolButton_05->setMinimumSize(QSize(16, 16));
        toolButton_05->setMaximumSize(QSize(16, 16));
        toolButton_05->setAutoFillBackground(true);
        toolButton_05->setAutoRaise(true);
        splitter->addWidget(toolButton_05);
        toolButton_06 = new QToolButton(splitter);
        toolButton_06->setObjectName(QString::fromUtf8("toolButton_06"));
        toolButton_06->setMinimumSize(QSize(16, 16));
        toolButton_06->setMaximumSize(QSize(16, 16));
        toolButton_06->setAutoFillBackground(true);
        toolButton_06->setAutoRaise(true);
        splitter->addWidget(toolButton_06);
        toolButton_07 = new QToolButton(splitter);
        toolButton_07->setObjectName(QString::fromUtf8("toolButton_07"));
        toolButton_07->setMinimumSize(QSize(16, 16));
        toolButton_07->setMaximumSize(QSize(16, 16));
        toolButton_07->setAutoFillBackground(true);
        toolButton_07->setAutoRaise(true);
        splitter->addWidget(toolButton_07);
        splitter_3->addWidget(splitter);
        splitter_2 = new QSplitter(splitter_3);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        splitter_2->setMinimumSize(QSize(135, 18));
        splitter_2->setMaximumSize(QSize(135, 16));
        splitter_2->setAutoFillBackground(true);
        splitter_2->setLineWidth(2);
        splitter_2->setMidLineWidth(2);
        splitter_2->setOrientation(Qt::Horizontal);
        splitter_2->setOpaqueResize(false);
        splitter_2->setHandleWidth(1);
        toolButton_08 = new QToolButton(splitter_2);
        toolButton_08->setObjectName(QString::fromUtf8("toolButton_08"));
        toolButton_08->setMinimumSize(QSize(16, 16));
        toolButton_08->setMaximumSize(QSize(16, 16));
        toolButton_08->setAutoFillBackground(true);
        toolButton_08->setAutoRaise(true);
        splitter_2->addWidget(toolButton_08);
        toolButton_09 = new QToolButton(splitter_2);
        toolButton_09->setObjectName(QString::fromUtf8("toolButton_09"));
        toolButton_09->setMinimumSize(QSize(16, 16));
        toolButton_09->setMaximumSize(QSize(16, 16));
        toolButton_09->setAutoFillBackground(true);
        toolButton_09->setAutoRaise(true);
        splitter_2->addWidget(toolButton_09);
        toolButton_10 = new QToolButton(splitter_2);
        toolButton_10->setObjectName(QString::fromUtf8("toolButton_10"));
        toolButton_10->setMinimumSize(QSize(16, 16));
        toolButton_10->setMaximumSize(QSize(16, 16));
        toolButton_10->setAutoFillBackground(true);
        toolButton_10->setAutoRaise(true);
        splitter_2->addWidget(toolButton_10);
        toolButton_11 = new QToolButton(splitter_2);
        toolButton_11->setObjectName(QString::fromUtf8("toolButton_11"));
        toolButton_11->setMinimumSize(QSize(16, 16));
        toolButton_11->setMaximumSize(QSize(16, 16));
        toolButton_11->setAutoFillBackground(true);
        toolButton_11->setAutoRaise(true);
        splitter_2->addWidget(toolButton_11);
        toolButton_12 = new QToolButton(splitter_2);
        toolButton_12->setObjectName(QString::fromUtf8("toolButton_12"));
        toolButton_12->setMinimumSize(QSize(16, 16));
        toolButton_12->setMaximumSize(QSize(16, 16));
        toolButton_12->setAutoFillBackground(true);
        toolButton_12->setAutoRaise(true);
        splitter_2->addWidget(toolButton_12);
        toolButton_13 = new QToolButton(splitter_2);
        toolButton_13->setObjectName(QString::fromUtf8("toolButton_13"));
        toolButton_13->setMinimumSize(QSize(16, 16));
        toolButton_13->setMaximumSize(QSize(16, 16));
        toolButton_13->setAutoFillBackground(true);
        toolButton_13->setAutoRaise(true);
        splitter_2->addWidget(toolButton_13);
        toolButton_14 = new QToolButton(splitter_2);
        toolButton_14->setObjectName(QString::fromUtf8("toolButton_14"));
        toolButton_14->setMinimumSize(QSize(16, 16));
        toolButton_14->setMaximumSize(QSize(16, 16));
        toolButton_14->setAutoFillBackground(true);
        toolButton_14->setAutoRaise(true);
        splitter_2->addWidget(toolButton_14);
        toolButton_15 = new QToolButton(splitter_2);
        toolButton_15->setObjectName(QString::fromUtf8("toolButton_15"));
        toolButton_15->setMinimumSize(QSize(16, 16));
        toolButton_15->setMaximumSize(QSize(16, 16));
        toolButton_15->setAutoFillBackground(true);
        toolButton_15->setAutoRaise(true);
        splitter_2->addWidget(toolButton_15);
        splitter_3->addWidget(splitter_2);

        horizontalLayout->addWidget(splitter_3);


        retranslateUi(ToolbarCommon);

        QMetaObject::connectSlotsByName(ToolbarCommon);
    } // setupUi

    void retranslateUi(QWidget *ToolbarCommon)
    {
        ToolbarCommon->setWindowTitle(QCoreApplication::translate("ToolbarCommon", "Form", nullptr));
        title->setText(QString());
        toolButton_00->setText(QString());
        toolButton_01->setText(QString());
        toolButton_02->setText(QString());
        toolButton_03->setText(QString());
        toolButton_04->setText(QString());
        toolButton_05->setText(QString());
        toolButton_06->setText(QString());
        toolButton_07->setText(QString());
        toolButton_08->setText(QString());
        toolButton_09->setText(QString());
        toolButton_10->setText(QString());
        toolButton_11->setText(QString());
        toolButton_12->setText(QString());
        toolButton_13->setText(QString());
        toolButton_14->setText(QString());
        toolButton_15->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ToolbarCommon: public Ui_ToolbarCommon {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TOOLBARCOMMON_H
