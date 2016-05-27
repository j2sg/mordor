#include "bot.h"
#include <qxmpp/QXmppMucManager.h>
#include <qxmpp/QXmppDiscoveryManager.h>
#include <QRegExp>
#include <QDebug>

Bot *Bot::instance()
{
    static Bot bot;

    return &bot;
}

void Bot::connected()
{
    qDebug() << "Bot connected to" << configuration().domain();

    _discoveryManager -> requestItems("conference.jabber.odyssey.net");
}

void Bot::itemsReceived(const QXmppDiscoveryIq& response)
{
    QList<QXmppDiscoveryIq::Item> rooms = response.items();
    QRegExp pattern("m0rd0r(\\d+)@(\\S+)");

    foreach(QXmppDiscoveryIq::Item room, rooms) {
        if(pattern.exactMatch(room.jid()))
            _mucManager -> addRoom(room.jid());
    }

    foreach(QXmppMucRoom * room, _mucManager -> rooms()) {
        if(room -> participants().length() < 10) {
            room -> setNickName("bot");
            room -> join();
            break;
        }
    }

}

Bot::Bot(QObject *parent) : QXmppClient(parent)
{
    createManagers();
    createConnections();
}

void Bot::createManagers()
{
    _mucManager = new QXmppMucManager;
    _discoveryManager = findExtension<QXmppDiscoveryManager>();

    addExtension(_mucManager);
}

void Bot::createConnections()
{
    connect(this, SIGNAL(connected()), this, SLOT(connected()));
    connect(_discoveryManager, SIGNAL(itemsReceived(const QXmppDiscoveryIq&)), this, SLOT(itemsReceived(const QXmppDiscoveryIq&)));
}
