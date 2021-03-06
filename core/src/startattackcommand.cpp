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

#include "startattackcommand.h"
#include <QJsonDocument>
#include <QJsonObject>

StartAttackCommand::StartAttackCommand(const QString& target, int id, const QString& from, const QString& to)
    : Message(id, from, to), _target(target)
{}

void StartAttackCommand::setTarget(const QString& target)
{
    _target = target;
}

const QString& StartAttackCommand::target() const
{
    return _target;
}

void StartAttackCommand::fromJson(const QString& json)
{
    QJsonDocument document = QJsonDocument::fromJson(json.toUtf8());
    QJsonObject documentObject = document.object();

    _id = documentObject["id"].toInt();
    _target = documentObject["target"].toString();
}

QString StartAttackCommand::toJson() const
{
    QJsonObject documentObject;

    documentObject["id"] = _id;
    documentObject["type"] = "START_ATTACK_CMD";
    documentObject["target"] = _target;

    return QJsonDocument(documentObject).toJson(QJsonDocument::Compact);
}
