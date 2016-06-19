#include "storagemanager.h"
#include <QSettings>

bool StorageManager::existsConfig()
{
    QSettings setting("config.ini", QSettings::IniFormat);

    return setting.value("Executed", false).toBool();
}

bool StorageManager::createConfig(bool overwrite)
{
    if(existsConfig() && !overwrite)
        return false;

    QSettings setting("config.ini", QSettings::IniFormat);

    setting.setValue("Executed", true);
    setting.setValue("jid",      "");
    setting.setValue("password", "");

    return true;
}

QVariant StorageManager::readConfig(const QString& key)
{
    if(!existsConfig())
        return QVariant();

    QSettings setting("config.ini", QSettings::IniFormat);

    return setting.value(key);
}

bool StorageManager::writeConfig(const QString& key, const QVariant& value)
{
    if(!existsConfig())
        return false;

    QSettings setting("config.ini", QSettings::IniFormat);

    if(!setting.contains(key))
        return false;

    setting.setValue(key, value);

    return true;
}
