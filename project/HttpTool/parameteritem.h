#ifndef PARAMETERITEM_H
#define PARAMETERITEM_H

#include <QWidget>

namespace Ui {
class ParameterItem;
}

class ParameterItem : public QWidget
{
    Q_OBJECT

public:
    explicit ParameterItem(QWidget *parent = 0, QString strFlag = "");
    ~ParameterItem();

    void initValue(QString strKey, QString strValue);
    QString getKey();
    QString getValue();
signals:
    void sigCloseMe(QString strFlag, QString strKey, QString strValue);

private slots:
    void on_pushButtonDel_clicked();

private:
    Ui::ParameterItem *ui;

    QString m_strFlag;
    QString m_strKey;
    QString m_strValue;
};

#endif // PARAMETERITEM_H
