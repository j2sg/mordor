#include "xmppclient.h"
#include "getstatuscommand.h"
#include "botstateresponse.h"
#include <qxmpp/QXmppMucManager.h>
#include <qxmpp/QXmppMessage.h>
#include <QDebug>

XmppClient::XmppClient(const QString& resource, const QString& roomName, const QString& muc, QObject *parent)
    : QXmppClient(parent), _resource(resource), _roomName(roomName), _muc(muc)
{
    _room = 0;

    createConnections();
}

void XmppClient::connectToServer(const QString &jid, const QString &password)
{
    QXmppConfiguration configuration;

    configuration.setResource(_resource);
    configuration.setJid(jid);
    configuration.setPassword(password);

    QXmppClient::connectToServer(configuration);
}

void XmppClient::sendCommand(const Message& command)
{
    _room -> sendMessage(command.toJson());
}

void XmppClient::sendResponse(const Message& response)
{
    _room -> sendMessage(response.toJson());
}

void XmppClient::connectedOnXmppClient()
{
    qDebug() << "Connected to server" << configuration().domain();

    joinRoom();
}

void XmppClient::errorOnXmppClient(QXmppClient::Error error)
{
    qDebug() << "Error on client:" << error;
}

void XmppClient::messageReceivedOnRoom(const QXmppMessage& xmppMessage)
{
    if(xmppMessage.type() == QXmppMessage::GroupChat) {
        Message *message = Message::createFromJson(xmppMessage.body());
        message -> setFrom(xmppMessage.from());

        if(dynamic_cast<GetStatusCommand *>(message) != 0)
            emit commandReceived(*message);
        else if(dynamic_cast<BotStateResponse *>(message) != 0)
            emit responseReceived(*message);

        delete message;
    }
}

void XmppClient::joinRoom()
{
    if(!_room) {
        QXmppMucManager *manager = findExtension<QXmppMucManager>();

        if(!manager) {
            manager = new QXmppMucManager;
            addExtension(manager);
        }

        _room = manager -> addRoom(QString("%1@%2.%3").arg(_roomName)
                                                      .arg(_muc)
                                                      .arg(configuration().domain()));

        _room -> setNickName(configuration().jid().split('@').at(0));

        createRoomConnections();
    }

    _room -> join();
}

void XmppClient::createConnections()
{
    connect(this, SIGNAL(connected()),
            this, SLOT(connectedOnXmppClient()));
    connect(this, SIGNAL(error(QXmppClient::Error)),
            this, SLOT(errorOnXmppClient(QXmppClient::Error)));
}

void XmppClient::createRoomConnections()
{
    connect(_room, SIGNAL(joined()),
            this, SIGNAL(ready()));
    connect(_room, SIGNAL(messageReceived(const QXmppMessage&)),
            this, SLOT(messageReceivedOnRoom(QXmppMessage)));
    connect(_room, SIGNAL(participantAdded(const QString&)),
            this, SIGNAL(botAdded(const QString&)));
    connect(_room, SIGNAL(participantRemoved(const QString&)),
            this, SIGNAL(botRemoved(const QString&)));
}
