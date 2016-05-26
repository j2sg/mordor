#include "botmanager.h"

BotManager *BotManager::instance()
{
    static BotManager manager;

    return &manager;
}

bool BotManager::start() const
{
    _bot -> connectToServer("j2sg@jabber.odyssey.net", "161t80u33x");

    return true;
}

BotManager::BotManager()
{
    _bot = Bot::instance();
}
