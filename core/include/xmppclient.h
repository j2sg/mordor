#ifndef XMPPCLIENT_H
#define XMPPCLIENT_H

#include <qxmpp/QXmppClient.h>

#define DEFAULT_ROOM_NAME "m0rd0r"
#define DEFAULT_MUC       "conference"

class QXmppMucRoom;
class Command;

class XmppClient : public QXmppClient
{
    Q_OBJECT
public:
    XmppClient(const QString& resource,
               const QString& roomName = DEFAULT_ROOM_NAME,
               const QString& muc = DEFAULT_MUC, QObject *parent = 0);
signals:
    void ready();
    void botAdded(const QString &jid);
    void botRemoved(const QString &jid);
public slots:
    void connectToServer(const QString &jid, const QString &password);
    void sendCommand(const Command& command);
private slots:
    void connectedOnXmppClient();
    void errorOnXmppClient(QXmppClient::Error error);
    void messageReceivedOnXmppClient(const QXmppMessage& message);
private:
    void joinRoom();
    void createConnections();

    QString _resource;
    QString _roomName;
    QString _muc;
    QXmppMucRoom *_room;
};

#endif // XMPPCLIENT_H
