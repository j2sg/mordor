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

#ifndef XMPPCLIENT_H
#define XMPPCLIENT_H

#include "core_global.h"
#include <qxmpp/QXmppClient.h>

#define DEFAULT_ROOM_NAME "m0rd0r"
#define DEFAULT_MUC       "conference"

class QXmppMucRoom;
class Message;

class CORE_EXPORT XmppClient : public QXmppClient
{
    Q_OBJECT
public:
    XmppClient(const QString& resource,
               const QString& roomName = DEFAULT_ROOM_NAME,
               const QString& muc = DEFAULT_MUC, QObject *parent = 0);
    QString whoAmI();
    QString whoAmIOnRoom();
signals:
    void ready();
    void commandReceived(Message *command);
    void responseReceived(Message *response);
    void badMessageReceived(const QString& message);
    void botAdded(const QString &jid);
    void botRemoved(const QString &jid);
public slots:
    void connectToServer(const QString &jid, const QString &password);
    void sendCommand(const Message& command);
    void sendResponse(const Message& response);
private slots:
    void joinRoom();
    void messageReceivedOnRoom(const QXmppMessage& xmppMessage);
private:
    void createConnections();
    void createRoomConnections();

    QString _resource;
    QString _roomName;
    QString _muc;
    QXmppMucRoom *_room;
};

#endif // XMPPCLIENT_H
