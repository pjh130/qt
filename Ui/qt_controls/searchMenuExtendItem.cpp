#include "searchMenuExtendItem.h"
#include "ui_searchMenuExtendItem.h"

searchMenuExtendItem::searchMenuExtendItem(QWidget *parent) :
    comboItem(parent),
    ui(new Ui::searchMenuExtendItem)
{
    ui->setupUi(this);

    m_bActived = false;
    setAutoFillBackground(true);
}

searchMenuExtendItem::~searchMenuExtendItem()
{
    delete ui;
}

void searchMenuExtendItem::setInfo(const QPixmap &pixmap, const QString &strText)
{
    ui->label_picture->setPixmap(pixmap);
    ui->label_String->setText(strText);
}


void searchMenuExtendItem::setActiveStatue(bool bActive)
{
    m_bActived = bActive;
    update();
}

void searchMenuExtendItem::paintEvent(QPaintEvent *ev)
{
    if (m_bActived)
    {

    }

    comboItem::paintEvent(ev);
}
