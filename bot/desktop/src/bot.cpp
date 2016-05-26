#include "bot.h"

Bot *Bot::instance()
{
    static Bot bot;

    return &bot;
}

Bot::Bot(QObject *parent) : QXmppClient(parent)
{}
