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

#ifndef XMPPREGCLIENT_H
#define XMPPREGCLIENT_H

#include "core_global.h"
#include <qxmpp/QXmppClient.h>
#include <QStringList>

#define CREDENTIAL_LENGTH_BY_DEFAULT 10

class CORE_EXPORT XmppRegClient : public QXmppClient
{
    Q_OBJECT
public:
    XmppRegClient(const QString& server, QObject *parent = 0);
signals:
    void success(const QString& server, const QString& username, const QString& password);
    void failure(const QString& server, const QString& username, const QString& password);
public slots:
    void sendRegistrationRequest();
private slots:
    void connectedOnClient();
    void iqReceivedOnClient(const QXmppIq& iq);
    void errorOnClient(QXmppClient::Error error);
private:
    void connectToServer(const QXmppConfiguration& configuration, const QXmppPresence& initialPresence = QXmppPresence());
    void connectToServer(const QString& jid, const QString& password);
    void createConnections();
    static QStringList generateRandomCredentials(int length = CREDENTIAL_LENGTH_BY_DEFAULT);

    QString _server;
    static const int _port = 5222;
    QString _username;
    QString _password;
};

#endif // XMPPREGCLIENT_H
