#ifndef BOT_H
#define BOT_H

#include <qxmpp/QXmppClient.h>

class Bot : public QXmppClient
{
    Q_OBJECT
public:
    static Bot *instance();
private slots:
    void connected();
    void messageReceived(const QXmppMessage& message);
    void error(QXmppClient::Error error);
private:
    Bot(QObject *parent = 0);
    ~Bot() {}
    void createConnections();
    void joinRoom();
};

#endif // BOT_H
