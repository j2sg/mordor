#include "xmppclient.h"
#include "global.h"
#include <qxmpp/QXmppMucManager.h>
#include <QDebug>

XmppClient::XmppClient(QObject *parent) : QXmppClient(parent)
{
    createConnections();
}

void XmppClient::connectToServer(const QString &jid, const QString &password)
{
    QXmppConfiguration configuration;

    configuration.setResource(APPLICATION_NAME);
    configuration.setJid(jid);
    configuration.setPassword(password);

    QXmppClient::connectToServer(configuration);
}

void XmppClient::connectedOnXmppClient()
{
    qDebug() << "Connected to server";

    joinRoom();

    emit ready();
}

void XmppClient::errorOnXmppClient(QXmppClient::Error error)
{
    qDebug() << "Error on client";
}

void XmppClient::messageReceivedOnXmppClient(const QXmppMessage& message)
{
    qDebug() << "Message received on client";
}

void XmppClient::joinRoom()
{
    QXmppMucManager *manager = findExtension<QXmppMucManager>();

    if(!manager) {
        manager = new QXmppMucManager;
        addExtension(manager);
    }

    QXmppMucRoom *room = manager -> addRoom(QString("%1@%2.%3")
                                            .arg(ROOM)
                                            .arg(DEFAULT_MUC)
                                            .arg(configuration().domain()));

    room -> setNickName(NICKNAME);
    room -> join();
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
