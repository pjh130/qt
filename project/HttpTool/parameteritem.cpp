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
    emit sigCloseMe(m_strFlag, m_strKey, m_strValue);
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
    return m_strKey;
}

QString ParameterItem::getValue()
{
    return m_strValue;
}
