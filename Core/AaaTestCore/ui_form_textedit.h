/********************************************************************************
** Form generated from reading UI file 'form_textedit.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_TEXTEDIT_H
#define UI_FORM_TEXTEDIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <texteditex.h>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton_insertimage;
    QPushButton *pushButton_clear;
    TextEditEx *textEdit;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(451, 386);
        verticalLayout = new QVBoxLayout(Form);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        pushButton_insertimage = new QPushButton(Form);
        pushButton_insertimage->setObjectName(QString::fromUtf8("pushButton_insertimage"));

        verticalLayout->addWidget(pushButton_insertimage);

        pushButton_clear = new QPushButton(Form);
        pushButton_clear->setObjectName(QString::fromUtf8("pushButton_clear"));

        verticalLayout->addWidget(pushButton_clear);

        textEdit = new TextEditEx(Form);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));

        verticalLayout->addWidget(textEdit);


        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QCoreApplication::translate("Form", "Form", nullptr));
        pushButton_insertimage->setText(QCoreApplication::translate("Form", "\346\217\222\345\205\245\345\233\276\347\211\207", nullptr));
        pushButton_clear->setText(QCoreApplication::translate("Form", "\346\270\205\347\220\206", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_TEXTEDIT_H
