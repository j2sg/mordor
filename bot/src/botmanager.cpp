#include "botmanager.h"
#include "global.h"
#include "xmppclient.h"
#include "storagemanager.h"
#include "getstatuscommand.h"
#include "botstateresponse.h"
#include <QDebug>

BotManager *BotManager::instance()
{
    static BotManager manager;

    return &manager;
}

bool BotManager::start() const
{
    QString jid = StorageManager::readConfig("jid").toString();
    QString password = StorageManager::readConfig("password").toString();

    _bot -> connectToServer(jid, password);

    return true;
}


bool BotManager::stop() const
{
    _bot -> disconnectFromServer();

    return true;
}

void BotManager::commandReceivedOnBot(const Message& command)
{
    qDebug() << "Command received from" << command.from();
}

BotManager::BotManager()
{
    if(setup())
        _bot = new XmppClient(APPLICATION_NAME);

    createConnections();
}

BotManager::~BotManager()
{
    stop();

    delete _bot;
}

bool BotManager::setup()
{
    if(!StorageManager::existsConfig()) {
        StorageManager::createConfig();
        StorageManager::writeConfig("jid", "bot1@jabber.odyssey.net");
        StorageManager::writeConfig("password", "1234");
    }

    return true;
}

void BotManager::createConnections()
{
    connect(_bot, SIGNAL(commandReceived(const Message&)),
            this, SLOT(commandReceivedOnBot(const   Message&)));
}
