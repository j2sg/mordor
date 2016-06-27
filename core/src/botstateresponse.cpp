#include "botstateresponse.h"
#include "bot.h"
#include <QJsonDocument>
#include <QJsonObject>

BotStateResponse::BotStateResponse(Bot *bot, int id, const QString& from)
    : Message(id, from), _bot(bot)
{}

BotStateResponse::BotStateResponse(const BotStateResponse& botStateResponse) : Message(botStateResponse)
{
    *this = botStateResponse;
}

BotStateResponse::~BotStateResponse()
{
    if(_bot)
        delete _bot;
}

BotStateResponse& BotStateResponse::operator=(const BotStateResponse& botStateResponse)
{
    Message::operator=(botStateResponse);

    if(_bot)
        delete _bot;

    _bot = botStateResponse._bot ? new Bot(*botStateResponse._bot) : 0;

    return *this;
}

void BotStateResponse::setBot(Bot *bot)
{
    if(_bot)
        delete _bot;

    _bot = bot;
}

const Bot *BotStateResponse::bot() const
{
    return _bot;
}

void BotStateResponse::fromJson(const QString& json)
{
    QJsonDocument document = QJsonDocument::fromJson(json.toUtf8());
    QJsonObject documentObject = document.object();

    _id = documentObject["id"].toInt();

    QJsonObject botObject = documentObject["bot"].toObject();

    QString botId = botObject["id"].toString();
    QString botIp = botObject["ip"].toString();
    QString botOs = botObject["os"].toString();
    BotState botState = static_cast<BotState>(botObject["state"].toInt());
    int botAttackId = botObject["attack"].toInt();

    _bot = new Bot(botId, botIp, botOs, botState, botAttackId);
}

QString BotStateResponse::toJson() const
{
    QJsonObject documentObject;

    documentObject["id"] = _id;
    documentObject["type"] = "BOT_STATE_RES";

    QJsonObject botObject;

    botObject["id"] = _bot -> id();
    botObject["ip"] = _bot -> ip();
    botObject["os"] = _bot -> os();
    botObject["state"] = static_cast<int>(_bot -> state());
    botObject["attack"] = _bot -> attackId();

    documentObject["bot"] = botObject;

    return QJsonDocument(documentObject).toJson(QJsonDocument::Compact);
}
