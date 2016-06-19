#ifndef BOTMANAGER_H
#define BOTMANAGER_H

class XmppClient;

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

    XmppClient *_bot;
};

#endif // BOTMANAGER_H
