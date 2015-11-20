#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonFile_clicked()
{
    QString str = QFileDialog::getOpenFileName(this);

    if (str.isEmpty())
    {
        return;
    }

    ui->lineEditFile->setText(str);
}

void MainWindow::on_pushButtonSubmit_clicked()
{
    QString strUrl = ui->lineEditUrl->text().trimmed();
    if (strUrl.isEmpty())
    {
        QMessageBox::warning(this, "Error", "Url is empty!");
        return;
    }

    if (ui->radioButtonFile->isChecked())
    {
        QString strFile = ui->lineEditFile->text().trimmed();
        if (strFile.isEmpty())
        {
            QMessageBox::warning(this, "Error", "Choose file path!");
        }
        return;
    }

}
