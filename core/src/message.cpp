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

#include "message.h"
#include "getbotstatecommand.h"
#include "startattackcommand.h"
#include "stopattackcommand.h"
#include "botstateresponse.h"
#include "attackstartedresponse.h"
#include "attackstoppedresponse.h"
#include <QJsonDocument>
#include <QJsonObject>

Message::Message(int id, const QString& from, const QString& to) : _id(id), _from(from), _to(to)
{}

void Message::setId(int id)
{
    _id = id;
}

int Message::id() const
{
    return _id;
}

void Message::setFrom(const QString& from)
{
    _from = from;
}

const QString& Message::from() const
{
    return _from;
}

void Message::setTo(const QString& to)
{
    _to = to;
}

const QString& Message::to() const
{
    return _to;
}

Message *Message::createFromJson(const QString& json)
{
    QJsonDocument document = QJsonDocument::fromJson(json.toUtf8());
    QJsonObject object = document.object();

    Message *message = Message::getInstanceOf(object["type"].toString());

    if(message)
        message -> fromJson(json);

    return message;
}

Message *Message::getInstanceOf(const QString& type)
{
    if(type == "GET_BOT_STATE_CMD")
        return new GetBotStateCommand;
    else if(type == "START_ATTACK_CMD")
        return new StartAttackCommand;
    else if(type == "STOP_ATTACK_CMD")
        return new StopAttackCommand;
    else if(type == "BOT_STATE_RES")
        return new BotStateResponse;
    else if(type == "ATTACK_STARTED_RES")
        return new AttackStartedResponse;
    else if(type == "ATTACK_STOPPED_RES")
        return new AttackStoppedResponse;

    return 0;
}
