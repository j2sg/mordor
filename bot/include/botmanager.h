#ifndef BOTMANAGER_H
#define BOTMANAGER_H

#include "bot.h"

class BotManager
{
public:
    static BotManager *instance();
    bool start() const;
    bool stop() const;
private:
    BotManager();
    BotManager(const BotManager& /*botManager*/) {}
    BotManager& operator=(const BotManager& /*botManager*/) { return *this; }
    ~BotManager() {}

    Bot *_bot;
};

#endif // BOTMANAGER_H
