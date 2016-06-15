#ifndef STORAGEMANAGER_H
#define STORAGEMANAGER_H

class StorageManager
{
public:
    static bool existsConfig();
    static bool createConfig(bool overwrite = false);
};

#endif // STORAGEMANAGER_H
