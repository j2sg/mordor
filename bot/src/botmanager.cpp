#include "botmanager.h"
#include "storagemanager.h"
#include <QDebug>

BotManager *BotManager::instance()
{
    static BotManager manager;

    return &manager;
}

bool BotManager::start() const
{
    bool existsConfig = StorageManager::existsConfig();
    qDebug() << "Exists Config?" << (existsConfig ? "Yes" : "No");

    if(!existsConfig)
        StorageManager::createConfig();

    _bot -> connectToServer("bot1@jabber.odyssey.net", "1234");

    return true;
}


bool BotManager::stop() const
{
    _bot -> disconnectFromServer();

    return true;
}

BotManager::BotManager()
{
    _bot = Bot::instance();
}
