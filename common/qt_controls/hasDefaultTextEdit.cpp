#include "hasDefaultTextEdit.h"

hasDefaultTextEdit::hasDefaultTextEdit(QWidget *parent) :
    QLineEdit(parent)
{
    m_bEmpty = true;

    m_echoDefaultMode = Normal;
    m_echoMode = echoMode();

    setText("");

    connect(this, SIGNAL(textChanged(QString)), this, SLOT(slot_textChanged(QString)));
}

void hasDefaultTextEdit::setText(const QString &strText)
{
    m_bEmpty = strText.isEmpty();
    if (m_bEmpty)
    {
        QLineEdit::setEchoMode(m_echoDefaultMode);
        QLineEdit::setText(m_strDefaultText);
    }
    else
    {
        QLineEdit::setEchoMode(m_echoMode);
        QLineEdit::setText(strText);
    }
}

void hasDefaultTextEdit::clear()
{
    setText("");
}

QString hasDefaultTextEdit::text()
{
    if (m_bEmpty)
    {
        return "";
    }
    else
    {
        return QLineEdit::text();
    }
}

void hasDefaultTextEdit::setDefaultText(const QString &strtext, EchoMode echoMode)
{
    m_strDefaultText = strtext;
    m_echoDefaultMode = echoMode;

    setText(text());
}

void hasDefaultTextEdit::setEchoMode(EchoMode echoMode)
{
    m_echoMode = echoMode;
    if (!m_bEmpty)
    {
        QLineEdit::setEchoMode(m_echoMode);
    }
}

void hasDefaultTextEdit::slot_textChanged(const QString &strText)
{
    if (!m_bEmpty)
    {
        emit editTextChanged(strText);
    }
}

void hasDefaultTextEdit::focusInEvent(QFocusEvent *event)
{
    QLineEdit::focusInEvent(event);

    if (m_bEmpty)
    {
        QLineEdit::setEchoMode(m_echoMode);
        QLineEdit::setText("");
    }

    m_bEmpty = false;
}

void hasDefaultTextEdit::focusOutEvent(QFocusEvent *event)
{
    QLineEdit::focusOutEvent(event);

    setText(text());
}
