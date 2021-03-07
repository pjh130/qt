#include "recttoolbar.h"
#include "ui_recttoolbar.h"

RectToolBar::RectToolBar(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::RectToolBar)
{
    ui->setupUi(this);
    lineWidth = defauleLineWidth;
    colorUsed = defaultColor;
    ui->toolButton_1->setChecked(true);

    connect(ui->toolButton_1,SIGNAL(clicked()),this,SLOT(Clicked_1()));
    connect(ui->toolButton_2,SIGNAL(clicked()),this,SLOT(Clicked_2()));
    connect(ui->toolButton_3,SIGNAL(clicked()),this,SLOT(Clicked_3()));
    connect(ui->widget,SIGNAL(selColorChanged(QColor)),this,SLOT(lineColorChanged(QColor)));
}

RectToolBar::~RectToolBar()
{
    delete ui;
}

qreal RectToolBar::getLineWidth()
{
    return lineWidth;
}

QColor RectToolBar::getLineColor()
{
    return colorUsed;
}

void RectToolBar::Clicked_1 ( bool checked)
{
    checked = checked;
    lineWidth = defauleLineWidth;
    ui->toolButton_2->setChecked(false);
    ui->toolButton_3->setChecked(false);

    ui->toolButton_1->setChecked(true);
    emit attrChanged();
}

void RectToolBar::Clicked_2 ( bool checked)
{
    checked = checked;
    lineWidth = defauleLineWidth * 2;
    ui->toolButton_1->setChecked(false);
    ui->toolButton_3->setChecked(false);

    ui->toolButton_2->setChecked(true);
    emit attrChanged();
}

void RectToolBar::Clicked_3 ( bool checked)
{
    checked = checked;
    lineWidth = defauleLineWidth * 4;
    ui->toolButton_1->setChecked(false);
    ui->toolButton_2->setChecked(false);

    ui->toolButton_3->setChecked(true);
    emit attrChanged();
}

void RectToolBar::lineColorChanged(QColor color)
{
    colorUsed = color;
    emit attrChanged();
}
