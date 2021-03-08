#include "form_textedit.h"
#include "ui_form_textedit.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_QuitOnClose);

    setWindowTitle("TextEdit");
    resize(800, 1000);
}

Form::~Form()
{
    delete ui;
}

void Form::on_pushButton_insertimage_clicked()
{
    QString strFile = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                   QDir::currentPath(),
                                                   tr("Images (*.gif *.png *.xpm *.jpg)"));
    if (strFile.isEmpty())
    {
        return;
    }

    ui->textEdit->insertRichText(strFile);
}

void Form::on_pushButton_clear_clicked()
{
    ui->textEdit->clear();
}
