#include "numberButton.h"
//#include "ui_numberButton.h"
#include "ui_numberButton.h"

numberButton::numberButton(QWidget *parent) :
    QWidget(parent), ui(new Ui::numberButton)
{
    ui->setupUi(this);

    setNumber(0);
}

numberButton::~numberButton()
{
    delete ui;
}

void numberButton::setNumber(qint32 iNumber)
{
    m_iNumber = iNumber;

    ui->label_text->setText("(" + QString::number(iNumber) + ")");
}

void numberButton::setIcon(const QPixmap &pximap)
{
    ui->label_picture->setPixmap(pximap);
}

void numberButton::mouseReleaseEvent(QMouseEvent *ev)
{
    QWidget::mouseReleaseEvent(ev);

    emit clicked();
}
