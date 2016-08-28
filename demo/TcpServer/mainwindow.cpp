#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QHostAddress>

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

void MainWindow::on_pushButton_listen_clicked()
{
    QString strPort = ui->lineEdit_port->text();
    if (strPort.isEmpty())
    {
        qDebug()<<"Port is empty"<<endl;
        return;
    }

    if (m_tcpServer.isListening())
    {
        qDebug()<<"Server is listening"<<endl;
        return;
    }

    if (!m_tcpServer.listen(QHostAddress::Any, strPort.toInt()))
    {
        qDebug()<<"Listen port: "<<strPort<<" error. "<<m_tcpServer.errorString()<<endl;
        return;
    }

    qDebug()<<"Start listen port: "<<strPort<<endl;
}
