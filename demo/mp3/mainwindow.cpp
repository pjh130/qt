#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMediaPlayer>

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
    player->setMedia(QUrl::fromLocalFile(str));
    player->setVolume(50);
    player->play();
}
