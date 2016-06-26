#ifndef BOTMANAGER_H
#define BOTMANAGER_H

#include <QObject>

class XmppClient;
class Message;

class BotManager : public QObject
{
    Q_OBJECT
public:
    static BotManager *instance();
    bool start() const;
    bool stop() const;
private slots:
    void commandReceivedOnBot(const Message& command);
private:
    BotManager();
    ~BotManager();
    bool setup();
    void createConnections();

    XmppClient *_bot;
};

#endif // BOTMANAGER_H
