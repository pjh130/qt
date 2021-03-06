#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <windows.h>
#include "logex.h"
#include "emailex.h"
#include "networkaccessmanagerex.h"
#include "tcpserver.h"
#include "JlCompress.h"
#include "excelbase.h"
#include "threadhandle.h"
#include "sqliteex.h"
#include "mysqlex.h"
#include "psqlex.h"
#include "odbcex.h"
#include "direx.h"
#include "fileex.h"
#include "systemex.h"
#include "stringex.h"
#include "timeex.h"
#include "imageex.h"
#include "textcodecex.h"
#include "settingsex.h"
#include "capturewidget.h"
#include <QShortcut>
#include <QHotkey>
#include <form_textedit.h>
#include "tcchinese.h"
#include "tcpsocketclient.h"
#include "blurWindow.h"
#include "windowframe.h"
#include "mywidget.h"
#include "parser.h"
#include "searchresultwidget.h"

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
    void testOdbc();
    void testPsql();
    void testHttp();

private slots:
    void on_pushButton_email_clicked();

    void on_pushButton_excel_clicked();

    void on_pushButton_log_clicked();

    void on_pushButton_network_clicked();

    void on_pushButton_zip_clicked();

    void on_pushButton_thread_clicked();

    void slotWorkResult(REPLY_ST st);

    void on_pushButton_sql_clicked();

    void on_pushButton_file_clicked();

    void on_pushButton_time_clicked();

    void on_pushButton_os_clicked();

    void on_pushButton_string_clicked();

    void on_pushButton_textcodec_clicked();

    void on_pushButton_image_clicked();

    void on_pushButton_settings_clicked();

    void on_pushButton_ScreenShot_clicked();

    void slotFinishPixmap(const QPixmap &finishPixmap);

    void on_pushButton_qxtglobalshortcut_clicked();

    void on_pushButton_textedit_clicked();

    void on_pushButton_frame_clicked();

signals:
    void clientSendData(SEND_DATA_ST st);
    void sendDisConnect(int i);
    void addWork(REQUEST_ST request);
    void startCaptureWidget();

private:
    Ui::MainWindow *ui;
    //    FullScreenWidget *fullWidget;
    CaptureWidget *captureWidget;
    QHotkey *hotkey;
};

#endif // MAINWINDOW_H
