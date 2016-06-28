#include "xmppclient.h"
#include "getstatuscommand.h"
#include "getbotstatecommand.h"
#include "startattackcommand.h"
#include "stopattackcommand.h"
#include "botstateresponse.h"
#include "attackstartedresponse.h"
#include "attackstoppedresponse.h"
#include <qxmpp/QXmppMucManager.h>
#include <qxmpp/QXmppMessage.h>

XmppClient::XmppClient(const QString& resource, const QString& roomName, const QString& muc, QObject *parent)
    : QXmppClient(parent), _resource(resource), _roomName(roomName), _muc(muc)
{
    _room = 0;

    createConnections();
}

QString XmppClient::whoAmI()
{
    return configuration().jid();
}

QString XmppClient::whoAmIOnRoom()
{
    return QString("%1/%2").arg(_room -> jid()).arg(_room -> nickName());
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
    if(command.to().isEmpty())
        _room -> sendMessage(command.toJson());
    else
        sendMessage(command.to(), command.toJson());
}

void XmppClient::sendResponse(const Message& response)
{
    if(response.to().isEmpty())
        _room -> sendMessage(response.toJson());
    else
        sendMessage(response.to(), response.toJson());
}

void XmppClient::connectedOnXmppClient()
{
    joinRoom();
}

void XmppClient::messageReceivedOnRoom(const QXmppMessage& xmppMessage)
{
    if(xmppMessage.type() == QXmppMessage::Chat ||
       xmppMessage.type() == QXmppMessage::GroupChat) {
        if(xmppMessage.stamp().isNull()) {
            Message *message = Message::createFromJson(xmppMessage.body());

            if(!message) {
                emit badMessageReceived(xmppMessage.body());
            } else {
                message -> setFrom(xmppMessage.from());

                if(dynamic_cast<GetStatusCommand *>(message) ||
                   dynamic_cast<GetBotStateCommand *>(message) ||
                   dynamic_cast<StartAttackCommand *>(message) ||
                   dynamic_cast<StopAttackCommand *>(message))
                    emit commandReceived(message);
                else if(dynamic_cast<BotStateResponse *>(message) ||
                        dynamic_cast<AttackStartedResponse *>(message) ||
                        dynamic_cast<AttackStoppedResponse *>(message))
                    emit responseReceived(message);
            }
        }
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
