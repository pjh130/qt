#include "searchMenuItem.h"
#include "ui_searchMenuItem.h"

searchMenuItem::searchMenuItem(QWidget *parent) :
    comboItem(parent),
    ui(new Ui::searchMenuItem)
{
    ui->setupUi(this);
    enableMouseEnterEvent(false);
    ui->label_mainString->installEventFilter(this);
}

searchMenuItem::~searchMenuItem()
{
    delete ui;
}

void searchMenuItem::setInfo(const QPixmap &pixmap, const QString &strText)
{
    ui->label_Picture->setPixmap(pixmap);
    ui->label_mainString->setText(strText);
}

bool searchMenuItem::eventFilter(QObject *object, QEvent *ev)
{
    if (QEvent::MouseButtonRelease == ev->type())
    {
        if (object == ui->label_mainString)
        {
            this->event(ev);
            return true;
        }
    }

    return comboItem::eventFilter(object, ev);
}
