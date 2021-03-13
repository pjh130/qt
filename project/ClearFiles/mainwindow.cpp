#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Clear");
    ui->label_clear->setText(QString("( %1 )").arg(m_lst.length()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_choose_clicked()
{
    m_lst.clear();
    ui->textEdit->clear();
    ui->label_clear->setText(QString("( %1 )").arg(m_lst.length()));

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
    ui->label_clear->setText(QString("( %1 )").arg(m_lst.length()));
}

void MainWindow::on_pushButton_clear_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("The files has been delete");
    msgBox.setInformativeText("Do you want to delete?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    int ret = msgBox.exec();
    qDebug()<<"ret: "<<ret;

    switch (ret) {
    case QMessageBox::Yes:
        // Ignore the error
        if (true)
        {
            qDebug()<<"Start to delete...";
            int iTotal = m_lst.length();
            int iOk = 0;
            QString strFailed;
            QStringList lstFailed;
            while(!m_lst.isEmpty())
            {
                QString strRemove = m_lst.takeFirst();
                bool bOk = FileEx::removeFile(strRemove);
                if (bOk)
                {
                    iOk++;
                } else {
                    lstFailed<<strRemove;
                    strFailed = strFailed + strRemove + "\n";
                }
            }
            m_lst<<lstFailed;
            qDebug()<<"Finish to delete...";
            QString strShow = QString("Delete result: %1/%2\n").arg(iOk).arg(iTotal);
            if(!strFailed.isEmpty())
            {
                strShow = strShow + "\nFailed:\n";
                strShow = strShow + strFailed;
            }
            ui->textEdit->setText(strShow);
            ui->label_clear->setText(QString("( %1 )").arg(m_lst.length()));
        }
        break;
    case QMessageBox::No:
        //
        qDebug()<<"ret NO";
        return;
        break;
    default:
        // should never be reached
        return;
        break;
    }
}
