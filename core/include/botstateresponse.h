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

#ifndef BOTSTATERESPONSE_H
#define BOTSTATERESPONSE_H

#include "core_global.h"
#include "message.h"
#include "types.h"

class Bot;

class CORE_EXPORT BotStateResponse : public Message
{
public:
    BotStateResponse(Bot *bot = 0, int id = NO_MSG_ID, const QString& from = "", const QString& to = "");
    BotStateResponse(const BotStateResponse& botStateResponse);
    ~BotStateResponse();
    BotStateResponse& operator=(const BotStateResponse& botStateResponse);
    void setBot(Bot *bot);
    const Bot *bot() const;
    void fromJson(const QString& json);
    QString toJson() const;
protected:
    Bot *_bot;
};

#endif // BOTSTATERESPONSE_H
