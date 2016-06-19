#include "xmppclient.h"
#include "command.h"
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

void XmppClient::sendCommand(const Command& command)
{
    _room -> sendMessage(command.toJson());
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

void XmppClient::messageReceivedOnXmppClient(const QXmppMessage& message)
{
    qDebug() << "Message received on client";
    qDebug() << "Type:"  << message.type();
    qDebug() << "To:"    << message.to();
    qDebug() << "From:"    << message.from();
    qDebug() << "Stamp:" << message.stamp();
    qDebug() << "Body:"  << message.body();
}

void XmppClient::joinRoom()
{
    QXmppMucManager *manager = findExtension<QXmppMucManager>();

    if(!manager) {
        manager = new QXmppMucManager;
        addExtension(manager);
    }

    _room = manager -> addRoom(QString("%1@%2.%3").arg(_roomName)
                                                  .arg(_muc)
                                                  .arg(configuration().domain()));

    connect(_room, SIGNAL(joined()),
            this, SIGNAL(ready()));
    connect(_room, SIGNAL(participantAdded(const QString&)),
            this, SIGNAL(botAdded(const QString&)));
    connect(_room, SIGNAL(participantRemoved(const QString&)),
            this, SIGNAL(botRemoved(const QString&)));

    _room -> setNickName(configuration().jid().split('@').at(0));
    _room -> join();
}

void XmppClient::createConnections()
{
    connect(this, SIGNAL(connected()),
            this, SLOT(connectedOnXmppClient()));
    connect(this, SIGNAL(error(QXmppClient::Error)),
            this, SLOT(errorOnXmppClient(QXmppClient::Error)));
    connect(this, SIGNAL(messageReceived(const QXmppMessage&)),
            this, SLOT(messageReceivedOnXmppClient(const QXmppMessage&)));
}
