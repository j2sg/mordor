#include "bot.h"

Bot::Bot(const QString& id, const QString& ip, const QString& os, BotState state)
    : _id(id), _ip(ip), _os(os), _state(state) {}

const QString& Bot::id() const
{
    return _id;
}

const QString& Bot::ip() const
{
    return _ip;
}

const QString &Bot::os() const
{
    return _os;
}

void Bot::setState(BotState state)
{
    _state = state;
}

BotState Bot::state() const
{
    return _state;
}
