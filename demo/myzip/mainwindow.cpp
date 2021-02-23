#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "JlCompress.h"
#include <QDebug>

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

void MainWindow::on_pushButton_file_clicked()
{
    bool bRet = JlCompress::compressFile("D:\\test\\new\\file.tar", "D:\\test\\1.txt");
    qDebug()<<"compressFile result: "<<bRet;
}

void MainWindow::on_pushButton_files_clicked()
{
    QStringList files;
    files<<"D:\\test\\1.txt";
    files<<"D:\\test\\2.txt";
    files<<"D:\\test\\aaa\\3.txt";
    bool bRet = JlCompress::compressFiles("D:\\test\\new\\files.tar", files);
    qDebug()<<"compressFiles result: "<<bRet;
}

void MainWindow::on_pushButton_dir_clicked()
{
    bool bRet = JlCompress::compressDir("D:\\test\\new\\dir.tar", "D:\\test\\aaa");
    qDebug()<<"compressDir result: "<<bRet;
}

void MainWindow::on_pushButton_file_extract_clicked()
{
    QStringList ret = JlCompress::extractDir("D:\\test\\new\\file.tar", "D:\\test\\new\\up");
    qDebug()<<"extractDir result: "<<ret;
}


void MainWindow::on_pushButton_files_extract_clicked()
{
    QStringList ret = JlCompress::extractDir("D:\\test\\new\\files.tar", "D:\\test\\new\\up");
    qDebug()<<"extractDir result: "<<ret;
}

void MainWindow::on_pushButton_dir_extract_clicked()
{
    QStringList ret = JlCompress::extractDir("D:\\test\\new\\dir.tar", "D:\\test\\new\\up");
    qDebug()<<"extractDir result: "<<ret;

}
