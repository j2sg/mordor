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
#include <qxmpp/QXmppRegisterIq.h>
#include <QTime>

XmppRegClient::XmppRegClient(const QString& server, QObject *parent)
    : QXmppClient(parent), _server(server)
{
    createConnections();
}

void XmppRegClient::sendRegistrationRequest()
{
    QStringList credentials = generateRandomCredentials();

    _username = credentials[0];
    _password = credentials[1];

    QXmppConfiguration config;

    config.setHost(_server);
    config.setDomain(_server);
    config.setPort(_port);
    config.setUseSASLAuthentication(false);
    config.setUseNonSASLAuthentication(false);

    connectToServer(config);
}

void XmppRegClient::connectedOnClient()
{
    QXmppRegisterIq iq;

    iq.setId("reg1");
    iq.setType(QXmppIq::Get);
    iq.setTo(_server);

    sendPacket(iq);
}

void XmppRegClient::iqReceivedOnClient(const QXmppIq& iq)
{
    if(iq.type() == QXmppIq::Result) {
        if(iq.id() == "reg1") {
            QXmppRegisterIq setIq;

            setIq.setId("reg2");
            setIq.setType(QXmppIq::Set);
            setIq.setTo(_server);
            setIq.setUsername(_username);
            setIq.setPassword(_password);

            sendPacket(setIq);
        } else if(iq.id() == "reg2")
            emit success(_server, _username, _password);
    } else if(iq.type() == QXmppIq::Error)
        emit failure(_server, _username, _password);
}

void XmppRegClient::errorOnClient(QXmppClient::Error error)
{
    Q_UNUSED(error);

    emit failure(_server, _username, _password);
}

void XmppRegClient::connectToServer(const QXmppConfiguration& configuration, const QXmppPresence& initialPresence)
{
    QXmppClient::connectToServer(configuration, initialPresence);
}

void XmppRegClient::connectToServer(const QString& jid, const QString& password)
{
    QXmppClient::connectToServer(jid, password);
}

void XmppRegClient::createConnections()
{
    connect(this, SIGNAL(connected()),
            this, SLOT(connectedOnClient()));
    connect(this, SIGNAL(iqReceived(const QXmppIq&)),
            this, SLOT(iqReceivedOnClient(QXmppIq)));
    connect(this, SIGNAL(error(QXmppClient::Error)),
            this, SLOT(errorOnClient(QXmppClient::Error)));
}

QStringList XmppRegClient::generateRandomCredentials(int length)
{
    static bool ready = false;
    static QString alphabet;

    if(!ready) {
        qsrand((uint) QTime::currentTime().msec());

        for(int k = 'a'; k <= 'z'; ++k)
            alphabet += QChar(k);

        for(int k = 'A'; k <= 'Z'; ++k)
            alphabet += QChar(k);

        for(int k = '0'; k <= '9'; ++k)
            alphabet += QChar(k);

        ready = true;
    }

    QString username;
    QString password;

    while(length--) {
        username += alphabet.at(qrand() % alphabet.length());
        password += alphabet.at(qrand() % alphabet.length());
    }

    return QStringList() << username << password;
}
