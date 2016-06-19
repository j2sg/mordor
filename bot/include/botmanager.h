#ifndef BOTMANAGER_H
#define BOTMANAGER_H

#include <QObject>

class XmppClient;

class BotManager : public QObject
{
    Q_OBJECT
public:
    static BotManager *instance();
    bool start() const;
    bool stop() const;
private:
    BotManager();
    ~BotManager();
    bool setup();

    XmppClient *_bot;
};

#endif // BOTMANAGER_H
