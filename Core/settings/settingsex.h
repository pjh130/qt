#ifndef SETTINGSEX_H
#define SETTINGSEX_H
#include <QtCore>
#include <QSettings>

class SettingsEx
{
public:
    SettingsEx();
    ~SettingsEx();
    //读写ini文件
    static bool setValue(const QString &strInitPath, const QString &strGroup,
                         const QString &strKey, const QVariant &value);
    static QVariant getValue(const QString &strInitPath, const QString &strGroup,
                             const QString &strKey);
    static bool removeValue(const QString &strInitPath, const QString &strGroup,
                             const QString &strKey);

    //默认存储The scope is QSettings::UserScope and the format is
    //defaultFormat()(QSettings::NativeFormat by default)
    static bool setValue(const QString &strKey, const QVariant &value);
    static QVariant getValue(const QString &strKey);
    static bool removeValue(const QString &strKey);
};

#endif // SETTINGSEX_H
