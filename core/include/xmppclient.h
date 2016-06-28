#ifndef XMPPCLIENT_H
#define XMPPCLIENT_H

#include "core_global.h"
#include <qxmpp/QXmppClient.h>

#define DEFAULT_ROOM_NAME "m0rd0r"
#define DEFAULT_MUC       "conference"

class QXmppMucRoom;
class Message;

class CORE_EXPORT XmppClient : public QXmppClient
{
    Q_OBJECT
public:
    XmppClient(const QString& resource,
               const QString& roomName = DEFAULT_ROOM_NAME,
               const QString& muc = DEFAULT_MUC, QObject *parent = 0);
    QString whoAmI();
    QString whoAmIOnRoom();
signals:
    void ready();
    void commandReceived(Message *command);
    void responseReceived(Message *response);
    void badMessageReceived(const QString& message);
    void botAdded(const QString &jid);
    void botRemoved(const QString &jid);
public slots:
    void connectToServer(const QString &jid, const QString &password);
    void sendCommand(const Message& command);
    void sendResponse(const Message& response);
private slots:
    void connectedOnXmppClient();
    void errorOnXmppClient(QXmppClient::Error error);
    void messageReceivedOnRoom(const QXmppMessage& xmppMessage);
private:
    void joinRoom();
    void createConnections();
    void createRoomConnections();

    QString _resource;
    QString _roomName;
    QString _muc;
    QXmppMucRoom *_room;
};

#endif // XMPPCLIENT_H
