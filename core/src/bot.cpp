#include "bot.h"

Bot::Bot(const QString& id, const QString& ip, const QString& os, BotState state, const Attack& attack)
    : _id(id), _ip(ip), _os(os), _state(state), _attack(attack)
{}

void Bot::setId(const QString& id)
{
    _id = id;
}

const QString& Bot::id() const
{
    return _id;
}

void Bot::setIp(const QString& ip)
{
    _ip = ip;
}

const QString& Bot::ip() const
{
    return _ip;
}

void Bot::setOs(const QString& os)
{
    _os = os;
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

void Bot::setAttack(const Attack& attack)
{
    _attack = attack;
}

const Attack& Bot::attack() const
{
    return _attack;
}
