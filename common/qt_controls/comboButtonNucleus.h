#ifndef COMBOBUTTONNUCLEUS_H
#define COMBOBUTTONNUCLEUS_H

#include "combobutton.h"

class comboButtonNucleus : public comboButton
{
    Q_OBJECT

public:
    comboButtonNucleus(QWidget *parent = 0);
    ~comboButtonNucleus();
    void showDefaultSentence();
    virtual Key2Send getKey2Send();

signals:
    void defaultTextSelected(const QString &);

private:
    void getDefaultSentence(QStringList &listString, qint8 &i8DefaultIndex);

private slots:
    void slot_SentenceSelected(const QString &, bool bSetDefault);
    void slot_KeySendSelected(qint8 i8Key);
};

#endif
