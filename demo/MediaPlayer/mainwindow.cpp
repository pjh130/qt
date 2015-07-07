#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMediaPlayer>
#include <QDebug>
#include <QVideoWidget>

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

void MainWindow::on_pushButton_clicked()
{
    QString str = QFileDialog::getOpenFileName(this);

    if (str.isEmpty())
    {
        return;
    }

    QMediaPlayer *player = new QMediaPlayer;
//    connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    QUrl url = QUrl::fromLocalFile(str);


    qDebug()<<url.toString();
    player->setMedia(url);
    player->setVolume(50);

    QVideoWidget *videoWidget = new QVideoWidget();
    player->setVideoOutput(videoWidget);
    videoWidget->show();


    player->play();
}
