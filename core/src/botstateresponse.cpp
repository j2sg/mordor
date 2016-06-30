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

#include "botstateresponse.h"
#include "bot.h"
#include <QJsonDocument>
#include <QJsonObject>

BotStateResponse::BotStateResponse(Bot *bot, int id, const QString& from, const QString& to)
    : Message(id, from, to), _bot(bot)
{}

BotStateResponse::BotStateResponse(const BotStateResponse& botStateResponse) : Message(botStateResponse)
{
    *this = botStateResponse;
}

BotStateResponse::~BotStateResponse()
{
    if(_bot)
        delete _bot;
}

BotStateResponse& BotStateResponse::operator=(const BotStateResponse& botStateResponse)
{
    Message::operator=(botStateResponse);

    if(_bot)
        delete _bot;

    _bot = botStateResponse._bot ? new Bot(*botStateResponse._bot) : 0;

    return *this;
}

void BotStateResponse::setBot(Bot *bot)
{
    if(_bot)
        delete _bot;

    _bot = bot;
}

const Bot *BotStateResponse::bot() const
{
    return _bot;
}

void BotStateResponse::fromJson(const QString& json)
{
    QJsonDocument document = QJsonDocument::fromJson(json.toUtf8());
    QJsonObject documentObject = document.object();

    _id = documentObject["id"].toInt();

    QJsonObject botObject = documentObject["bot"].toObject();

    QString botId = botObject["id"].toString();
    QString botIp = botObject["ip"].toString();
    QString botOs = botObject["os"].toString();
    BotState botState = static_cast<BotState>(botObject["state"].toInt());

    QJsonObject attackObject = botObject["attack"].toObject();

    int attackId = attackObject["id"].toInt();
    QString attackTarget = attackObject["target"].toString();

    Attack botAttack(attackId, attackTarget);

    _bot = new Bot(botId, botIp, botOs, botState, botAttack);
}

QString BotStateResponse::toJson() const
{
    QJsonObject documentObject;

    documentObject["id"] = _id;
    documentObject["type"] = "BOT_STATE_RES";

    QJsonObject botObject;

    botObject["id"] = _bot -> id();
    botObject["ip"] = _bot -> ip();
    botObject["os"] = _bot -> os();
    botObject["state"] = static_cast<int>(_bot -> state());

    QJsonObject attackObject;

    attackObject["id"] = _bot -> attack().id();
    attackObject["target"] = _bot->attack().target();

    botObject["attack"] = attackObject;

    documentObject["bot"] = botObject;

    return QJsonDocument(documentObject).toJson(QJsonDocument::Compact);
}
