#ifndef PUBLIC_H
#define PUBLIC_H

#include <QWebView>
//#include <QtWebView/QtWebView>

extern QString g_strConfigSetup; //主配置文件 ":/settings/%1/setup.ini" //%1=g_strAppEnv

typedef enum
{
    onLine_On = 8,      // 在线
    onLine_Leave = 7,   // 离开
    onLine_Out = 3,     // 外出
    onLine_meeting = 6  // 开会
}onLineStatus;

extern void initWebView(QWebView &webview);

#endif // PUBLIC_H
