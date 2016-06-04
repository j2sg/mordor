#include "bot.h"
#include <qxmpp/QXmppMucManager.h>
#include <qxmpp/QXmppMessage.h>
#include <QDebug>

Bot *Bot::instance()
{
    static Bot bot;

    return &bot;
}

void Bot::connected()
{
    qDebug() << "Bot is connected to" << configuration().domain();

    joinRoom();

    qDebug() << "Bot has joined room m0rd0r@conference.jabber.odyssey.net";
}

void Bot::messageReceived(const QXmppMessage& message)
{
    qDebug() << message.body();
}

void Bot::error(QXmppClient::Error error)
{
    qDebug() << "Error:" << error;

    if(static_cast<int>(error) == 3) {
        qDebug() << xmppStreamError();
    }
}

Bot::Bot(QObject *parent) : QXmppClient(parent)
{
    createConnections();
}

void Bot::createConnections()
{
    connect(this, SIGNAL(connected()),
            this, SLOT(connected()));
    connect(this, SIGNAL(messageReceived(const QXmppMessage&)),
            this, SLOT(messageReceived(const QXmppMessage&)));
    connect(this, SIGNAL(error(QXmppClient::Error)),
            this, SLOT(error(QXmppClient::Error)));
}

void Bot::joinRoom()
{
    QXmppMucManager *mucManager = findExtension<QXmppMucManager>();

    if(mucManager == 0) {
        mucManager = new QXmppMucManager;
        addExtension(mucManager);
    }

    QXmppMucRoom *room = mucManager -> addRoom("m0rd0r@conference.jabber.odyssey.net");
    room -> setNickName("bot");
    room -> join();
}
