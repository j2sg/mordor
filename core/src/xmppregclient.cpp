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

#include "xmppregclient.h"
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

XmppRegClient::XmppRegClient(const QString& server, QObject *parent)
    : QObject(parent), _server(server)
{
    _socket = new QTcpSocket(this);

    createConnections();
}

void XmppRegClient::sendRegistrationRequest(const QString& username, const QString& password)
{
    // TO DO

    emit failure(_server, username, password);
}

void XmppRegClient::connectedOnSocket()
{
    qDebug() << "Connected to" << _server;
}

void XmppRegClient::disconnectedOnSocket()
{
    qDebug() << "Disconnected from" << _server;
}

void XmppRegClient::readyReadOnSocket()
{
    qDebug() << _socket -> readAll();
}

void XmppRegClient::errorOnSocket(QAbstractSocket::SocketError error)
{
    qDebug() << "Error:" << error;
}

void XmppRegClient::createConnections()
{
    connect(_socket,SIGNAL(connected()),
            this, SLOT(connectedOnSocket()));
    connect(_socket, SIGNAL(disconnected()),
            this, SLOT(disconnectedOnSocket()));
    connect(_socket, SIGNAL(readyRead()),
            this, SLOT(readyReadOnSocket()));
    connect(_socket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(errorOnSocket(QAbstractSocket::SocketError)));
}
