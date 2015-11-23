/********************************************************************************
** Form generated from reading UI file 'parameteritem.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARAMETERITEM_H
#define UI_PARAMETERITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ParameterItem
{
public:
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEditKey;
    QLineEdit *lineEditValue;
    QPushButton *pushButtonDel;

    void setupUi(QWidget *ParameterItem)
    {
        if (ParameterItem->objectName().isEmpty())
            ParameterItem->setObjectName(QStringLiteral("ParameterItem"));
        ParameterItem->resize(400, 23);
        horizontalLayout = new QHBoxLayout(ParameterItem);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        lineEditKey = new QLineEdit(ParameterItem);
        lineEditKey->setObjectName(QStringLiteral("lineEditKey"));

        horizontalLayout->addWidget(lineEditKey);

        lineEditValue = new QLineEdit(ParameterItem);
        lineEditValue->setObjectName(QStringLiteral("lineEditValue"));

        horizontalLayout->addWidget(lineEditValue);

        pushButtonDel = new QPushButton(ParameterItem);
        pushButtonDel->setObjectName(QStringLiteral("pushButtonDel"));

        horizontalLayout->addWidget(pushButtonDel);


        retranslateUi(ParameterItem);

        QMetaObject::connectSlotsByName(ParameterItem);
    } // setupUi

    void retranslateUi(QWidget *ParameterItem)
    {
        ParameterItem->setWindowTitle(QApplication::translate("ParameterItem", "Form", 0));
        pushButtonDel->setText(QApplication::translate("ParameterItem", "Delete", 0));
    } // retranslateUi

};

namespace Ui {
    class ParameterItem: public Ui_ParameterItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARAMETERITEM_H
