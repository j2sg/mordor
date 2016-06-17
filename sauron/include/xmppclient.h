#ifndef XMPPCLIENT_H
#define XMPPCLIENT_H

#include <qxmpp/QXmppClient.h>

class XmppClient : public QXmppClient
{
    Q_OBJECT
public:
    XmppClient(QObject *parent = 0);
signals:
    void ready();
public slots:
    void connectToServer(const QString &jid, const QString &password);
private slots:
    void connectedOnXmppClient();
    void errorOnXmppClient(QXmppClient::Error error);
    void messageReceivedOnXmppClient(const QXmppMessage& message);
private:
    void joinRoom();
    void createConnections();
};

#endif // XMPPCLIENT_H
