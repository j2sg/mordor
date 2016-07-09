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

#ifndef BOT_H
#define BOT_H

#include "core_global.h"
#include "types.h"
#include "attack.h"
#include <QString>

class CORE_EXPORT Bot
{
public:
    Bot(const QString& id = "", const QString& ip = "", const QString& os = "",
        BotState state = UndefinedState, const Attack& attack = Attack());
    void setId(const QString& id);
    const QString& id() const;
    void setIp(const QString& ip);
    const QString& ip() const;
    void setOs(const QString& os);
    const QString& os() const;
    void setState(BotState state);
    BotState state() const;
    void setAttack(const Attack& attack);
    const Attack& attack() const;
    QString toString() const;
private:
    QString _id;
    QString _ip;
    QString _os;
    BotState _state;
    Attack _attack;
};

#endif // BOT_H
