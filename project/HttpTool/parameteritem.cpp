#include "parameteritem.h"
#include "ui_parameteritem.h"

ParameterItem::ParameterItem(QWidget *parent, QString strFlag) :
    QWidget(parent),
    ui(new Ui::ParameterItem)
{
    ui->setupUi(this);

    m_strFlag = strFlag;
}

ParameterItem::~ParameterItem()
{
    delete ui;
}

void ParameterItem::on_pushButtonDel_clicked()
{
    emit sigCloseMe(m_strFlag, ui->lineEditKey->text().trimmed(), ui->lineEditValue->text().trimmed());
    //close();
}

void ParameterItem::initValue(QString strKey, QString strValue)
{
    m_strKey = strKey;
    m_strValue = strValue;

    ui->lineEditKey->setText(m_strKey);
    ui->lineEditValue->setText(m_strValue);
}

QString ParameterItem::getKey()
{
    return ui->lineEditKey->text().trimmed();
}

QString ParameterItem::getValue()
{
    return ui->lineEditValue->text().trimmed();
}
