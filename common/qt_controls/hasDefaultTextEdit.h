#ifndef HASDEFAULTTEXTEDIT_H
#define HASDEFAULTTEXTEDIT_H

#include <QLineEdit>

// 捕获此类的输入变化，不要使用textchanged信号，使用editTextChanged

class hasDefaultTextEdit : public QLineEdit
{
    Q_OBJECT

public:
    explicit hasDefaultTextEdit(QWidget *parent = 0);

    void setText(const QString &);
    QString text();
    void clear();
    void setEchoMode(EchoMode);
    void setDefaultText(const QString &, EchoMode echoMode = Normal);

signals:
    void editTextChanged(const QString &);

private slots:
    void slot_textChanged(const QString &);

private:
    void focusInEvent(QFocusEvent *);
    void focusOutEvent(QFocusEvent *);

private:
    QString m_strDefaultText;
    bool m_bEmpty;
    EchoMode m_echoMode;
    EchoMode m_echoDefaultMode;
};

#endif // HASDEFAULTTEXTEDIT_H
