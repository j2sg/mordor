/**
 *  This file is part of Mordor.
 *
 *  Copyright (c) 2016 Juan Jose Salazar Garcia jjslzgc@gmail.com
 *
 *  Mordor is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Mordor is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Mordor.  If not, see <http://www.gnu.org/licenses/>.
 *
 **/

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
