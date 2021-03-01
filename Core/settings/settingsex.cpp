#include "settingsex.h"

SettingsEx::SettingsEx()
{

}

SettingsEx::~SettingsEx()
{

}

bool SettingsEx::setValue(const QString &strInitPath, const QString &strGroup,
                          const QString &strKey, const QVariant &value)
{
    QFileInfo info(strInitPath);
    QDir dir(info.absoluteDir());
    if (!dir.exists())
    {
        dir.mkdir(info.absolutePath());
    }

    QSettings setting(strInitPath ,QSettings::IniFormat);
    // 分组保存
    setting.beginGroup(strGroup);
    setting.setValue(strKey, value);
    setting.endGroup();

    return true;
}

QVariant SettingsEx::getValue(const QString &strInitPath, const QString &strGroup,
                              const QString &strKey)
{
    QSettings setting(strInitPath, QSettings::IniFormat);

    setting.beginGroup(strGroup);
    QVariant value = setting.value(strKey);
    setting.endGroup();

    return value;
}

bool SettingsEx::removeValue(const QString &strInitPath, const QString &strGroup,
                             const QString &strKey)
{
    QSettings setting(strInitPath, QSettings::IniFormat);
    setting.remove(strGroup + "/" + strKey);

    return true;
}

bool SettingsEx::setValue(const QString &strKey, const QVariant &value)
{
    QSettings setting;

    setting.setValue(strKey, value);

    return true;
}

QVariant SettingsEx::getValue(const QString &strKey)
{
    QSettings setting;

    QVariant value = setting.value(strKey);

    return value;
}

bool SettingsEx::removeValue(const QString &strKey)
{
    QSettings setting;
    setting.remove(strKey);

    return true;
}
