#ifndef FORM_TEXTEDIT_H
#define FORM_TEXTEDIT_H

#include <QWidget>
#include <QFileDialog>
#include <QFile>
#include "textcodecex.h"

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();

private slots:
    void on_pushButton_insertimage_clicked();

    void on_pushButton_clear_clicked();

private:
    Ui::Form *ui;
};

#endif // FORM_TEXTEDIT_H
