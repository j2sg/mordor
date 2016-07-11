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

#ifndef ATTACKER_H
#define ATTACKER_H

#include <QObject>
#include <QString>

#define RPS_BY_DEFAULT 10

class QNetworkAccessManager;

class Attacker : public QObject
{
    Q_OBJECT
public:
    Attacker(ushort requestPerSecond = RPS_BY_DEFAULT);
    void setTarget(const QString &target);
signals:
    void done();
public slots:
    void attack();
private slots:
    void sendHttpGetRequestToTarget();
private:
    QString _target;
    ushort _requetsPerSecond;
    QNetworkAccessManager *_networkAccessManager;
};

#endif // ATTACKER_H
