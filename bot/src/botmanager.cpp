#include "botmanager.h"
#include "global.h"
#include "xmppclient.h"
#include "storagemanager.h"
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

BotManager::BotManager()
{
    if(setup())
        _bot = new XmppClient(APPLICATION_NAME);
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
