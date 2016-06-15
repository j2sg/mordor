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

    return true;
}
