#include "comboButtonNucleus.h"
#include "in_database.h"

comboButtonNucleus::comboButtonNucleus(QWidget *parent) : comboButton(parent)
{
    connect(this, SIGNAL(SentenceSelected(QString,bool)), this, SLOT(slot_SentenceSelected(QString,bool)));
    connect(this, SIGNAL(KeySendSelected(qint8)), this, SLOT(slot_KeySendSelected(qint8)));
}

comboButtonNucleus::~comboButtonNucleus()
{

}

void comboButtonNucleus::slot_SentenceSelected(const QString &strText, bool bSetDefault)
{
    if (bSetDefault)
    {

    }
    else
    {
        emit defaultTextSelected(strText);
    }
}

void comboButtonNucleus::slot_KeySendSelected(qint8 i8Key)
{
    if (NULL != g_pDatabase)
    {
        if (!g_pDatabase->setSendHotKey(i8Key))
        {
            qDebug("save hot key fail");
        }
    }
}

void comboButtonNucleus::getDefaultSentence(QStringList &listString, qint8 &i8DefaultIndex)
{
    listString.clear();

    listString.push_back("answer later");
    i8DefaultIndex = 0;
}

void comboButtonNucleus::showDefaultSentence()
{
    QStringList listString;
    qint8 i8Index = 0;
    getDefaultSentence(listString, i8Index);
    setDefaultSentance(listString, i8Index);

    comboButton::showDefaultSentence();
}

Key2Send comboButtonNucleus::getKey2Send()
{
    Key2Send key = Enter2Send;

    if (NULL != g_pDatabase)
    {
        int iKey = 0;
        if (g_pDatabase->getSendHotKey(iKey))
        {
            key = (Key2Send)iKey;
        }
    }

    return key;
}
