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

#ifndef MESSAGE_H
#define MESSAGE_H

#include "core_global.h"
#include <QString>

#define NO_MSG_ID -1

class CORE_EXPORT Message
{
public:
    Message(int id, const QString& from, const QString& to);
    virtual ~Message() {}
    void setId(int id);
    int id() const;
    void setFrom(const QString& from);
    const QString& from() const;
    void setTo(const QString& to);
    const QString& to() const;
    static Message *createFromJson(const QString& json);
    virtual void fromJson(const QString& json) = 0;
    virtual QString toJson() const = 0;
protected:
    int _id;
    QString _from;
    QString _to;
private:
    static Message *getInstanceOf(const QString& type);
};

#endif // MESSAGE_H
