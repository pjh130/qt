#include "public.h"
#include "idkin_common.h"

QString g_strConfigSetup; //主配置文件 ":/settings/${g_strAppEnv}/setup.ini"

void initWebView(QWebView &webview)
{
    webview.setAcceptDrops(false);

    QString strError;
    QString strSetting = getIniFileItem(g_strConfigSetup,
           "_QWebView", "DeveloperExtrasEnabled", strError);
    if (!strSetting.isEmpty())
    {
        webview.settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled,
                                         strSetting.toLower() == "true");
    }

    strSetting = getIniFileItem(g_strConfigSetup, "_QWebView", "PluginsEnabled", strError);
    if (!strSetting.isEmpty())
    {
        webview.settings()->setAttribute(QWebSettings::PluginsEnabled,
                                         strSetting.toLower() == "true");
    }

    strSetting = getIniFileItem(g_strConfigSetup, "_QWebView", "JavaEnabled", strError);
    if (!strSetting.isEmpty())
    {
        webview.settings()->setAttribute(QWebSettings::JavaEnabled,
                                         strSetting.toLower() == "true");
    }

    strSetting = getIniFileItem(g_strConfigSetup, "_QWebView",
                                "JavascriptCanAccessClipboard", strError);
    if (!strSetting.isEmpty())
    {
        webview.settings()->setAttribute(QWebSettings::JavascriptCanAccessClipboard,
                                         strSetting.toLower() == "true");
    }

    strSetting = getIniFileItem(g_strConfigSetup, "_QWebView",
                                "JavascriptCanOpenWindows", strError);
    if (!strSetting.isEmpty())
    {
        webview.settings()->setAttribute(QWebSettings::JavascriptCanOpenWindows,
                                         strSetting.toLower() == "true");
    }
}
