#ifndef BOT_H
#define BOT_H

#include <qxmpp/QXmppClient.h>

class QXmppMucManager;
class QXmppDiscoveryManager;

class Bot : public QXmppClient
{
    Q_OBJECT
public:
    static Bot *instance();
private slots:
    void connected();
    void itemsReceived(const QXmppDiscoveryIq& response);
private:
    Bot(QObject *parent = 0);
    ~Bot() {}
    void createManagers();
    void createConnections();

    QXmppMucManager *_mucManager;
    QXmppDiscoveryManager *_discoveryManager;
};

#endif // BOT_H
