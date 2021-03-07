#include "toolbarcommon.h"
#include "ui_toolbarcommon.h"
#include "globalDataType.h"
ToolbarCommon::ToolbarCommon(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ToolbarCommon)
{
    ui->setupUi(this);
    ui->title->setStyleSheet (QString("background:rgb(%1)").arg (ColorToString(colorPalette[0])));
    ui->toolButton_00->setStyleSheet (QString("background:rgb(%1)").arg (ColorToString(colorPalette[0])));
    ui->toolButton_01->setStyleSheet (QString("background:rgb(%1)").arg (ColorToString(colorPalette[1])));
    ui->toolButton_02->setStyleSheet (QString("background:rgb(%1)").arg (ColorToString(colorPalette[2])));
    ui->toolButton_03->setStyleSheet (QString("background:rgb(%1)").arg (ColorToString(colorPalette[3])));
    ui->toolButton_04->setStyleSheet (QString("background:rgb(%1)").arg (ColorToString(colorPalette[4])));
    ui->toolButton_05->setStyleSheet (QString("background:rgb(%1)").arg (ColorToString(colorPalette[5])));
    ui->toolButton_06->setStyleSheet (QString("background:rgb(%1)").arg (ColorToString(colorPalette[6])));
    ui->toolButton_07->setStyleSheet (QString("background:rgb(%1)").arg (ColorToString(colorPalette[7])));
    ui->toolButton_08->setStyleSheet (QString("background:rgb(%1)").arg (ColorToString(colorPalette[8])));
    ui->toolButton_09->setStyleSheet (QString("background:rgb(%1)").arg (ColorToString(colorPalette[9])));
    ui->toolButton_10->setStyleSheet (QString("background:rgb(%1)").arg (ColorToString(colorPalette[10])));
    ui->toolButton_11->setStyleSheet (QString("background:rgb(%1)").arg (ColorToString(colorPalette[11])));
    ui->toolButton_12->setStyleSheet (QString("background:rgb(%1)").arg (ColorToString(colorPalette[12])));
    ui->toolButton_13->setStyleSheet (QString("background:rgb(%1)").arg (ColorToString(colorPalette[13])));
    ui->toolButton_14->setStyleSheet (QString("background:rgb(%1)").arg (ColorToString(colorPalette[14])));
    ui->toolButton_15->setStyleSheet (QString("background:rgb(%1)").arg (ColorToString(colorPalette[15])));


    connect(ui->toolButton_00,SIGNAL(clicked()),this,SLOT(btnClicked00()));
    connect(ui->toolButton_01,SIGNAL(clicked()),this,SLOT(btnClicked01()));
    connect(ui->toolButton_02,SIGNAL(clicked()),this,SLOT(btnClicked02()));
    connect(ui->toolButton_03,SIGNAL(clicked()),this,SLOT(btnClicked03()));
    connect(ui->toolButton_04,SIGNAL(clicked()),this,SLOT(btnClicked04()));
    connect(ui->toolButton_05,SIGNAL(clicked()),this,SLOT(btnClicked05()));
    connect(ui->toolButton_06,SIGNAL(clicked()),this,SLOT(btnClicked06()));
    connect(ui->toolButton_07,SIGNAL(clicked()),this,SLOT(btnClicked07()));
    connect(ui->toolButton_08,SIGNAL(clicked()),this,SLOT(btnClicked08()));
    connect(ui->toolButton_09,SIGNAL(clicked()),this,SLOT(btnClicked09()));
    connect(ui->toolButton_10,SIGNAL(clicked()),this,SLOT(btnClicked10()));
    connect(ui->toolButton_11,SIGNAL(clicked()),this,SLOT(btnClicked11()));
    connect(ui->toolButton_12,SIGNAL(clicked()),this,SLOT(btnClicked12()));
    connect(ui->toolButton_13,SIGNAL(clicked()),this,SLOT(btnClicked13()));
    connect(ui->toolButton_14,SIGNAL(clicked()),this,SLOT(btnClicked14()));
    connect(ui->toolButton_15,SIGNAL(clicked()),this,SLOT(btnClicked15()));
}

ToolbarCommon::~ToolbarCommon()
{
    delete ui;
}

void ToolbarCommon::btnClicked00()
{
    selColor = colorPalette[0];
    ui->title->setStyleSheet (QString("background:rgb(%1)").arg (ColorToString(selColor)));
    emit selColorChanged(selColor);
}

void ToolbarCommon::btnClicked01()
{
    selColor = colorPalette[1];
    ui->title->setStyleSheet (QString("background:rgb(%1)").arg (ColorToString(selColor)));
    emit selColorChanged(selColor);
}
void ToolbarCommon::btnClicked02()
{
    selColor = colorPalette[2];
    ui->title->setStyleSheet (QString("background:rgb(%1)").arg (ColorToString(selColor)));
    emit selColorChanged(selColor);
}
void ToolbarCommon::btnClicked03()
{
    selColor = colorPalette[3];
    ui->title->setStyleSheet (QString("background:rgb(%1)").arg (ColorToString(selColor)));
    emit selColorChanged(selColor);
}
void ToolbarCommon::btnClicked04()
{
    selColor = colorPalette[4];
    ui->title->setStyleSheet (QString("background:rgb(%1)").arg (ColorToString(selColor)));
    emit selColorChanged(selColor);
}
void ToolbarCommon::btnClicked05()
{
    selColor = colorPalette[5];
    ui->title->setStyleSheet (QString("background:rgb(%1)").arg (ColorToString(selColor)));
    emit selColorChanged(selColor);
}
void ToolbarCommon::btnClicked06()
{
    selColor = colorPalette[6];
    ui->title->setStyleSheet (QString("background:rgb(%1)").arg (ColorToString(selColor)));
    emit selColorChanged(selColor);
}
void ToolbarCommon::btnClicked07()
{
    selColor = colorPalette[7];
    ui->title->setStyleSheet (QString("background:rgb(%1)").arg (ColorToString(selColor)));
    emit selColorChanged(selColor);
}
void ToolbarCommon::btnClicked08()
{
    selColor = colorPalette[8];
    ui->title->setStyleSheet (QString("background:rgb(%1)").arg (ColorToString(selColor)));
    emit selColorChanged(selColor);
}
void ToolbarCommon::btnClicked09()
{
    selColor = colorPalette[9];
    ui->title->setStyleSheet (QString("background:rgb(%1)").arg (ColorToString(selColor)));
    emit selColorChanged(selColor);
}
void ToolbarCommon::btnClicked10()
{
    selColor = colorPalette[10];
    ui->title->setStyleSheet (QString("background:rgb(%1)").arg (ColorToString(selColor)));
    emit selColorChanged(selColor);
}
void ToolbarCommon::btnClicked11()
{
    selColor = colorPalette[11];
    ui->title->setStyleSheet (QString("background:rgb(%1)").arg (ColorToString(selColor)));
    emit selColorChanged(selColor);
}
void ToolbarCommon::btnClicked12()
{
    selColor = colorPalette[12];
    ui->title->setStyleSheet (QString("background:rgb(%1)").arg (ColorToString(selColor)));
    emit selColorChanged(selColor);
}
void ToolbarCommon::btnClicked13()
{
    selColor = colorPalette[13];
    ui->title->setStyleSheet (QString("background:rgb(%1)").arg (ColorToString(selColor)));
    emit selColorChanged(selColor);
}
void ToolbarCommon::btnClicked14()
{
    selColor = colorPalette[14];
    ui->title->setStyleSheet (QString("background:rgb(%1)").arg (ColorToString(selColor)));
    emit selColorChanged(selColor);
}
void ToolbarCommon::btnClicked15()
{
    selColor = colorPalette[15];
    ui->title->setStyleSheet (QString("background:rgb(%1)").arg (ColorToString(selColor)));
    emit selColorChanged(selColor);
}
