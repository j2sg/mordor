#ifndef STORAGEMANAGER_H
#define STORAGEMANAGER_H

#include <QVariant>
#include <QString>

class StorageManager
{
public:
    static bool existsConfig();
    static bool createConfig(bool overwrite = false);
    static QVariant readConfig(const QString& key);
    static bool writeConfig(const QString& key, const QVariant& value);
};

#endif // STORAGEMANAGER_H
