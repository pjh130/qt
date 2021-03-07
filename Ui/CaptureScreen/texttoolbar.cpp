#include "texttoolbar.h"
#include "ui_texttoolbar.h"

TextToolBar::TextToolBar(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::TextToolBar)
{
    ui->setupUi(this);
    fontSize = defaultFontSize;
    connect(ui->comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(fontSizeChanged(int)));
    connect(ui->widget,SIGNAL(selColorChanged(QColor)),this,SLOT(fontColorChanged(QColor)));
}

TextToolBar::~TextToolBar()
{
    delete ui;
}

void TextToolBar::fontSizeChanged ( int index )
{
    switch(index)
    {
    case 0:
        fontSize = 8;
        break;
    case 1:
        fontSize = 9;
        break;
    case 2:
        fontSize = 10;
        break;
    case 3:
        fontSize = 11;
        break;
    case 4:
        fontSize = 12;
        break;
    case 5:
        fontSize = 14;
        break;
    case 6:
        fontSize = 16;
        break;
    case 7:
        fontSize = 18;
        break;
    case 8:
        fontSize = 20;
        break;
    default:
        fontSize = 8;
        break;
    }
    qDebug("font size:%d \n",fontSize);
    emit attrChanged();
}

void TextToolBar::fontColorChanged(QColor color)
{
    colorUsed = color;
    emit attrChanged();
}
