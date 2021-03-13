#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Clear");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_choose_clicked()
{
    m_lst.clear();
    ui->textEdit->clear();

    QString strDir = QFileDialog::getExistingDirectory(this);
    if (strDir.isEmpty())
    {
        return;
    }
    QStringList filters = ui->lineEdit_suffix->text().split(";");
    qDebug()<<"filters: "<<filters;
    m_lst = FileEx::allFiles(strDir,filters, true);
    QString strShow = QString("Find: %1\n").arg(m_lst.length());
    for(int i=0; i<m_lst.length(); i++)
    {
        strShow = strShow + m_lst.at(i) + "\n";
    }

    ui->textEdit->setText(strShow);

}

void MainWindow::on_pushButton_clear_clicked()
{

    for(int i=0; i<m_lst.length(); i++)
    {
        FileEx::removeFile(m_lst.at(i));
    }
    ui->textEdit->setText("Finished!");
}
