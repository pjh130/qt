/********************************************************************************
** Form generated from reading UI file 'recttoolbar.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RECTTOOLBAR_H
#define UI_RECTTOOLBAR_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>
#include "toolbarcommon.h"

QT_BEGIN_NAMESPACE

class Ui_RectToolBar
{
public:
    QHBoxLayout *horizontalLayout;
    QToolButton *toolButton_1;
    QToolButton *toolButton_2;
    QToolButton *toolButton_3;
    QFrame *line;
    ToolbarCommon *widget;

    void setupUi(QWidget *RectToolBar)
    {
        if (RectToolBar->objectName().isEmpty())
            RectToolBar->setObjectName(QString::fromUtf8("RectToolBar"));
        RectToolBar->resize(280, 40);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(RectToolBar->sizePolicy().hasHeightForWidth());
        RectToolBar->setSizePolicy(sizePolicy);
        RectToolBar->setMinimumSize(QSize(280, 40));
        RectToolBar->setMaximumSize(QSize(280, 40));
        RectToolBar->setAutoFillBackground(true);
        horizontalLayout = new QHBoxLayout(RectToolBar);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(1, 1, 1, 1);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetFixedSize);
        toolButton_1 = new QToolButton(RectToolBar);
        toolButton_1->setObjectName(QString::fromUtf8("toolButton_1"));
        toolButton_1->setMinimumSize(QSize(32, 32));
        toolButton_1->setMaximumSize(QSize(32, 32));
        toolButton_1->setFocusPolicy(Qt::NoFocus);
        toolButton_1->setAutoFillBackground(true);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/point01.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_1->setIcon(icon);
        toolButton_1->setIconSize(QSize(32, 32));
        toolButton_1->setCheckable(true);

        horizontalLayout->addWidget(toolButton_1);

        toolButton_2 = new QToolButton(RectToolBar);
        toolButton_2->setObjectName(QString::fromUtf8("toolButton_2"));
        toolButton_2->setMinimumSize(QSize(32, 32));
        toolButton_2->setMaximumSize(QSize(32, 32));
        toolButton_2->setAutoFillBackground(true);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/point02.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_2->setIcon(icon1);
        toolButton_2->setIconSize(QSize(32, 32));
        toolButton_2->setCheckable(true);

        horizontalLayout->addWidget(toolButton_2);

        toolButton_3 = new QToolButton(RectToolBar);
        toolButton_3->setObjectName(QString::fromUtf8("toolButton_3"));
        toolButton_3->setMinimumSize(QSize(32, 32));
        toolButton_3->setMaximumSize(QSize(32, 32));
        toolButton_3->setAutoFillBackground(true);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/point03.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_3->setIcon(icon2);
        toolButton_3->setIconSize(QSize(32, 32));
        toolButton_3->setCheckable(true);

        horizontalLayout->addWidget(toolButton_3);

        line = new QFrame(RectToolBar);
        line->setObjectName(QString::fromUtf8("line"));
        sizePolicy.setHeightForWidth(line->sizePolicy().hasHeightForWidth());
        line->setSizePolicy(sizePolicy);
        line->setMinimumSize(QSize(2, 32));
        line->setMaximumSize(QSize(2, 32));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line);

        widget = new ToolbarCommon(RectToolBar);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMinimumSize(QSize(176, 0));
        widget->setMaximumSize(QSize(176, 16777215));

        horizontalLayout->addWidget(widget);


        retranslateUi(RectToolBar);

        QMetaObject::connectSlotsByName(RectToolBar);
    } // setupUi

    void retranslateUi(QWidget *RectToolBar)
    {
        RectToolBar->setWindowTitle(QCoreApplication::translate("RectToolBar", "Form", nullptr));
        toolButton_1->setText(QCoreApplication::translate("RectToolBar", "1", nullptr));
        toolButton_2->setText(QCoreApplication::translate("RectToolBar", "2", nullptr));
        toolButton_3->setText(QCoreApplication::translate("RectToolBar", "3", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RectToolBar: public Ui_RectToolBar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RECTTOOLBAR_H
