#include "bot.h"
#include <QDebug>

Bot *Bot::instance()
{
    static Bot bot;

    return &bot;
}

void Bot::connected()
{
    qDebug() << "Bot connected to" << configuration().domain();
}

Bot::Bot(QObject *parent) : QXmppClient(parent)
{
    createConnections();
}

void Bot::createConnections()
{
    connect(this, SIGNAL(connected()), this, SLOT(connected()));
}
