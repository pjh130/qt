#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <windows.h>
#include "logex.h"
#include "email.h"
#include "networkaccessmanagerex.h"
#include "JlCompress.h"
#include "excelbase.h"
#include "threadhandle.h"
#include "sqliteex.h"
#include "mysqlex.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void testSqlite();
    void testMysql();

private slots:
    void on_pushButton_email_clicked();

    void on_pushButton_excel_clicked();

    void on_pushButton_log_clicked();

    void on_pushButton_network_clicked();

    void on_pushButton_zip_clicked();

    void on_pushButton_thread_clicked();

    void slotWorkResult(bool bOk, QString strTask, QByteArray data);

    void on_pushButton_sql_clicked();

signals:
    void addWork(REQUEST_ST request);
    void start();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
