#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkReply>
#include <QDebug>
#include <QUuid>
#include <QMap>
#include <QIODevice>
#include <QHttpMultiPart>
#include <QFile>

#include "parameteritem.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    enum MethodType {
        MethodGet = 0,
        MethodPost ,
        MethodPut,
        MethodDele,
        MethodPatch,
        MethodOption,
        MethodHead,
        MethodTrace,
        MethodConnect
    };

    enum BodyType {
        BodyFormdata = 0,
        BodyXwww ,
        BodyRaw,
        BodyBinary
    };

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void initWindow();

private slots:

    void on_pushButtonSubmit_clicked();

private slots:
    void httpFinished();
    void httpReadyRead();
    void updateDataReadProgress(qint64 bytesRead, qint64 totalBytes);

    void on_pushButtonHeader_clicked();
    void slotCloseHeaders(QString strFlag, QString strKey, QString strValue);

    void slotCloseFormdata(QString strFlag, QString strKey, QString strValue);
    void slotCloseXwww(QString strFlag, QString strKey, QString strValue);

    void slotCurrentIndexChanged(int index);

    void on_pushButtonAddFormdata_clicked();

    void on_pushButtonAddXwww_clicked();

    void on_pushButtonBinary_clicked();

    void on_pushButtonCopyHeaders_clicked();

    void on_pushButtonCopyContent_clicked();

private:
    QHttpMultiPart *getBodyDataFormdata();
    QByteArray getBodyDataXwww();
    QByteArray getBodyDataRaw();
    QIODevice *getBodyDataBinary();

private:
    QNetworkAccessManager qnam;
    QNetworkReply *reply;
    QByteArray byRecv;
    QString m_strMethod;

    QMap<QString, ParameterItem*> m_mapHeaders;
    QMap<QString, ParameterItem*> m_mapXwwwForm;
    QMap<QString, ParameterItem*> m_mapFormData;
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
