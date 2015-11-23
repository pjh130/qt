#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QLayout>
#include <QIODevice>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    reply = NULL;

    connect(ui->comboBoxMethod, SIGNAL(currentIndexChanged(int)), this, SLOT(slotCurrentIndexChanged(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initWindow()
{
    return;
    ui->tabWidgetRequest->widget(2)->hide();
}

QHttpMultiPart *MainWindow::getBodyDataFormdata()
{
    if (m_mapFormData.count() <=0)
    {
        return NULL;
    }

    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    QMap<QString, ParameterItem*>::iterator iter = m_mapFormData.begin();
    while(iter != m_mapFormData.end())
    {
        ParameterItem *pItem = iter.value();
        if (NULL != pItem)
        {
            QString strKey = pItem->getKey();
            QString strValue = pItem->getValue();
            if( !strValue.isEmpty() && !strKey.isEmpty())
            {
                qDebug()<<"key: "<<strKey;
                qDebug()<<"value: "<<strValue;
                QHttpPart textPart;
                textPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant(QString("form-data; name=\"%1\"").arg(strKey)));
//                textPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant(QString("form-data; name=\"%1\"; filename=\"%2\"").arg(strKey).arg("qt.txt")));
                textPart.setBody(strValue.toUtf8());
                multiPart->append(textPart);
            }
        }
        iter++;
    }

    if (0)
    {
        QHttpPart imagePart;
        QFile *file = new QFile("image.jpg");
        imagePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/jpeg"));
//                imagePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/x-msdownload"));
        imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant(QString("form-data; name=\"%1\"; filename=\"%2\"").arg("strKey").arg(file->fileName())));

        file->open(QIODevice::ReadOnly);
        imagePart.setBodyDevice(file);
        file->setParent(multiPart); // we cannot delete the file now, so delete it with the multiPart

        multiPart->append(imagePart);
    }

    return multiPart;
}

QByteArray MainWindow::getBodyDataXwww()
{
    QByteArray byData;
    QMap<QString, ParameterItem*>::iterator iter = m_mapXwwwForm.begin();
    while(iter != m_mapXwwwForm.end())
    {
        ParameterItem *pItem = iter.value();
        if (NULL != pItem)
        {
            QString strKey = pItem->getKey();
            QString strValue = pItem->getValue();
            if( !strValue.isEmpty() && !strKey.isEmpty())
            {
                if(byData.length()<=0)
                {
                    byData = byData + strKey.toUtf8().toPercentEncoding() + "=" + strValue.toUtf8().toPercentEncoding();
                } else {
                    byData = "&" + byData + strKey.toUtf8().toPercentEncoding() + "=" + strValue.toUtf8().toPercentEncoding();
                }
            }
        }
        iter++;
    }
    return byData;
}

QByteArray MainWindow::getBodyDataRaw()
{
    return ui->textEditRaw->toPlainText().toUtf8();
}

QIODevice *MainWindow::getBodyDataBinary()
{
    QString strFile = ui->lineEditBinary->text().trimmed();
    if (strFile.isEmpty())
    {
        qDebug()<<"strFile.isEmpty()";
        return NULL;
    }
    QFile *pF = new QFile(strFile);
    if (false == pF->open(QIODevice::ReadOnly))
    {
        qDebug()<<"strFile open fail:"<<pF->errorString();
        return NULL;
    }
    return pF;
}

void MainWindow::on_pushButtonSubmit_clicked()
{
    QString strUrl = ui->lineEditUrl->text().trimmed();
    if (strUrl.isEmpty())
    {
        QMessageBox::warning(this, "Error", "Url is empty!");
        return;
    }

    qDebug()<<"Start url request: "<<strUrl;


    QNetworkRequest request;
    request.setUrl(QUrl(strUrl));

    ////////////////setting headers////////////////
    QMap<QString, ParameterItem*>::iterator iter = m_mapHeaders.begin();
    while(iter != m_mapHeaders.end())
    {
        ParameterItem *pItem = iter.value();
        if (NULL != pItem)
        {
            QString strKey = pItem->getKey();
            QString strValue = pItem->getValue();
            qDebug()<<"key: "<<strKey;
            qDebug()<<"value: "<<strValue;

            if( !strValue.isEmpty() && !strKey.isEmpty())
            {
                request.setRawHeader(strKey.toUtf8(), strValue.toUtf8());
            }
        }
        iter++;
    }

    QIODevice *pF = NULL;
    QHttpMultiPart *multiPart = NULL;
    switch(ui->comboBoxMethod->currentIndex())
    {
    case MethodGet:
        m_strMethod = "GET";
        reply = qnam.get(request);
        break;
    case MethodPost:
        m_strMethod = "POST";
        switch (ui->tabWidgetBody->currentIndex()) {
        case BodyFormdata:
            multiPart = getBodyDataFormdata();
            if (NULL == multiPart)
            {
                QMessageBox::warning(this, "Error", "Form data is empty!");
                return;
            }
            reply = qnam.post(request, multiPart);
            multiPart->setParent(reply);
            break;
        case BodyXwww:
            reply = qnam.post(request, getBodyDataXwww());
            break;
        case BodyRaw:
            reply = qnam.post(request, getBodyDataRaw());
            break;
        case BodyBinary:
            pF = getBodyDataBinary();
            if (NULL == pF)
            {
                QMessageBox::warning(this, "Error", "Binary is empty!");
                return;
            }
            request.setHeader(QNetworkRequest::ContentTypeHeader, "application/octet-stream");
            reply = qnam.post(request, pF);
            pF->setParent(reply);
            break;
        default:
            QMessageBox::warning(this, "Error", "Body type error!");
            return;
        }
        break;
    case MethodPut:
        m_strMethod = "PUT";
        reply = qnam.put(request, "");
        break;
    case MethodDele:
        m_strMethod = "DELETE";
        QMessageBox::warning(this, "Error", "Method delete not support now!");
        return;
        break;
    case MethodPatch:
        m_strMethod = "PATHCH";
        QMessageBox::warning(this, "Error", "Method patch not support now!");
        return;
        break;
    case MethodOption:
        m_strMethod = "OPTION";
        QMessageBox::warning(this, "Error", "Method Option not support now!");
        return;
        break;
    case MethodHead:
        m_strMethod = "HEAD";
        reply = qnam.head(request);
        break;
    case MethodTrace:
        m_strMethod = "TRACE";
        QMessageBox::warning(this, "Error", "Method Trace not support now!");
        return;
        break;
    case MethodConnect:
        m_strMethod = "CONNECT";
        QMessageBox::warning(this, "Error", "Method Connect not support now!");
        return;
        break;
    default:
        break;
    }

    connect(reply, SIGNAL(finished()),
            this, SLOT(httpFinished()));
    connect(reply, SIGNAL(readyRead()),
            this, SLOT(httpReadyRead()));
    connect(reply, SIGNAL(downloadProgress(qint64,qint64)),
            this, SLOT(updateDataReadProgress(qint64,qint64)));

}

void MainWindow::httpFinished()
{
    if (NULL == reply)
    {
        qDebug()<<"reply NULL";
        return;
    }
    reply->ignoreSslErrors();
    QVariant status_code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
//    if (QNetworkReply::NoError == reply->error())
//    {
//        byRecv += reply->readAll();
//    } else {
//    }
    ui->labelStatus->setText(status_code.toString() + " " + reply->errorString());

    ui->labelUrl->setText(reply->url().toString());
    ui->labelMethod->setText(m_strMethod);
    ui->textEditResponse->setPlainText(byRecv);

    reply->deleteLater();
    reply = NULL;
}

void MainWindow::httpReadyRead()
{
    // this slot gets called every time the QNetworkReply has new data.
    // We read all of its new data and write it into the file.
    // That way we use less RAM than when reading it at the finished()
    // signal of the QNetworkReply
    byRecv += reply->readAll();
}

void MainWindow::updateDataReadProgress(qint64 bytesRead, qint64 totalBytes)
{
    //    qDebug()<<"bytesRead: "<<bytesRead;
    //    qDebug()<<"totalBytes: "<<totalBytes;
}

void MainWindow::on_pushButtonHeader_clicked()
{
    QString  strUuid = QUuid::createUuid().toString();
    ParameterItem *pItem = new ParameterItem(NULL, strUuid);
    connect(pItem,SIGNAL(sigCloseMe(QString,QString,QString)), this, SLOT(slotCloseHeaders(QString,QString,QString)));

    ui->verticalLayoutHeader->insertWidget(1, pItem);
    pItem->show();

    m_mapHeaders.insert(strUuid, pItem);
}

void MainWindow::slotCloseHeaders(QString strFlag, QString strKey, QString strValue)
{
    qDebug()<<"uuid: "<<strFlag;
    ParameterItem *pItem = m_mapHeaders.value(strFlag);
    if (NULL != pItem)
    {
        pItem->close();
        pItem->deleteLater();
    }
    m_mapHeaders.remove(strFlag);
}

void MainWindow::slotCloseXwww(QString strFlag, QString strKey, QString strValue)
{
    ParameterItem *pItem = m_mapXwwwForm.value(strFlag);
    if (NULL != pItem)
    {
        pItem->close();
        pItem->deleteLater();
    }
    m_mapXwwwForm.remove(strFlag);
}

void MainWindow::slotCloseFormdata(QString strFlag, QString strKey, QString strValue)
{
    ParameterItem *pItem = m_mapFormData.value(strFlag);
    if (NULL != pItem)
    {
        pItem->close();
        pItem->deleteLater();
    }
    m_mapFormData.remove(strFlag);
}

void MainWindow::slotCurrentIndexChanged(int index)
{

    switch(index)
    {
    case MethodGet:
        ui->tabWidgetRequest->widget(2)->hide();
        break;
    case MethodPost:
        ui->tabWidgetRequest->widget(2)->show();
        break;
    case MethodPut:
        ui->tabWidgetRequest->widget(2)->show();
        break;
    case MethodDele:
        ui->tabWidgetRequest->widget(2)->show();
        break;
    case MethodPatch:
        ui->tabWidgetRequest->widget(2)->show();
        break;
    case MethodOption:
        ui->tabWidgetRequest->widget(2)->hide();
        break;
    case MethodHead:
        ui->tabWidgetRequest->widget(2)->hide();
        break;
    case MethodTrace:
        ui->tabWidgetRequest->widget(2)->show();
        break;
    case MethodConnect:
        break;
    default:
        break;
    }
}

void MainWindow::on_pushButtonAddFormdata_clicked()
{
    QString  strUuid = QUuid::createUuid().toString();
    ParameterItem *pItem = new ParameterItem(NULL, strUuid);
    connect(pItem,SIGNAL(sigCloseMe(QString,QString,QString)), this, SLOT(slotCloseFormdata(QString,QString,QString)));

    ui->verticalLayoutFormdata->insertWidget(1, pItem);
    pItem->show();

    m_mapFormData.insert(strUuid, pItem);
}

void MainWindow::on_pushButtonAddXwww_clicked()
{
    QString  strUuid = QUuid::createUuid().toString();
    ParameterItem *pItem = new ParameterItem(NULL, strUuid);
    connect(pItem,SIGNAL(sigCloseMe(QString,QString,QString)), this, SLOT(slotCloseXwww(QString,QString,QString)));

    ui->verticalLayoutXwwForm->insertWidget(1, pItem);
    pItem->show();

    m_mapXwwwForm.insert(strUuid, pItem);
}

void MainWindow::on_pushButtonBinary_clicked()
{
    QString str = QFileDialog::getOpenFileName(this);

    if (str.isEmpty())
    {
        return;
    }

    ui->lineEditBinary->setText(str);
}
