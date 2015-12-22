#ifndef COMBOBUTTON_H
#define COMBOBUTTON_H

#include <QToolButton>
#include <QStringList>
#include <QMenu>

typedef enum
{
    Enter2Send = 0,
    CtrlEnter2Send
}Key2Send;

class comboButton : public QToolButton
{
    Q_OBJECT
public:
    explicit comboButton(QWidget *parent = 0);
    void showDefaultSentence();
    virtual Key2Send getKey2Send();

protected:
    void setDefaultSentance(const QStringList &listSentance, qint8 i8SelectedIndex);
    void keyPressEvent(QKeyEvent *event);

private:
    bool isInDownRect(const QPoint &point);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void setDefaultSend(qint32 iIndex);
    void setShutCut();

signals:
    void SentenceSelected(const QString &, bool bSetDefault);
    void KeySendSelected(qint8 i8Key);

private slots:
    void defaultSentenceSelected(QAction*);
    void defaultKeySelected(QAction*);

private:
    QMenu m_menuDefaultSentance;
    QAction *m_actionSetDefault;

    QMenu m_menuDefaultKey;
    QAction *m_actionEnter;
    QAction *m_actionCtrlEnter;
};

#endif // COMBOBUTTON_H
