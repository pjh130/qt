#include "comboboxitem.h"
#include "ui_comboBoxItem.h"
#include <QMouseEvent>

comboBoxItem::comboBoxItem(QWidget *parnet) : comboItem(parnet), ui(new Ui::comboBoxItem)
{
    ui->setupUi(this);

    m_bShowButton = false;
    m_bHaveButton = false;
}

comboBoxItem::~comboBoxItem()
{
    delete ui;
}

void comboBoxItem::setInfo(const QPixmap &pixmap, const QString &strMainText, const QString &strMinorText, bool bHaveButton)
{
    ui->label_image->setPixmap(pixmap);
    ui->label_mianString->setText(strMainText);
    ui->label_monitorString->setText(strMinorText);
    m_bHaveButton = bHaveButton;
}

void comboBoxItem::setShowButton(bool show)
{
    m_bShowButton = show;

    reSortUi();
}

void comboBoxItem::reSortUi()
{
    const int iControlDistance = 5;
    QSize sizeImage(height() - 8, height() - 8);
    QPoint posImage(10, 4);
    ui->label_image->resize(sizeImage);
    ui->label_image->move(posImage);

    QPoint pointMainString(posImage.rx() + sizeImage.width() + iControlDistance,
           (height() - ui->label_mianString->height() - ui->label_monitorString->height()) / 2);
    ui->label_mianString->move(pointMainString);
    QPoint pointMonitorString(pointMainString.rx(),
           pointMainString.ry() + ui->label_mianString->height());
    ui->label_monitorString->move(pointMonitorString);
    ui->label_mianString->resize(width() - pointMainString.rx(), ui->label_mianString->height());
    ui->label_monitorString->resize(ui->label_mianString->size());

    if (m_bHaveButton && m_bShowButton)
    {
        ui->pushButton->move(width() - iControlDistance * 2 - ui->pushButton->width(),
                             (height() - ui->pushButton->height()) / 2);
        ui->pushButton->raise();
        ui->pushButton->show();
    }
    else
    {
        ui->pushButton->hide();
    }
}

void comboBoxItem::resizeEvent(QResizeEvent *event)
{
    comboItem::resizeEvent(event);

    reSortUi();
}

void comboBoxItem::on_pushButton_clicked()
{
    emit buttonClicked(this);
}
