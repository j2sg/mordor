#include "botmanager.h"

BotManager *BotManager::instance()
{
    static BotManager manager;

    return &manager;
}

bool BotManager::start() const
{
    _bot -> connectToServer("bot1@jabber.odyssey.net", "1234");

    return true;
}

BotManager::BotManager()
{
    _bot = Bot::instance();
}
