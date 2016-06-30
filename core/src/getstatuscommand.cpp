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

#include "getstatuscommand.h"
#include <QJsonDocument>
#include <QJsonObject>

GetStatusCommand::GetStatusCommand(int id, const QString& from, const QString& to) : Message(id, from, to)
{}

void GetStatusCommand::fromJson(const QString& json)
{
    QJsonDocument document = QJsonDocument::fromJson(json.toUtf8());
    QJsonObject object = document.object();

    _id = object["id"].toInt();
}

QString GetStatusCommand::toJson() const
{
    QJsonObject object;

    object["id"] = _id;
    object["type"] = "GET_STATUS_CMD";

    return QJsonDocument(object).toJson(QJsonDocument::Compact);
}
