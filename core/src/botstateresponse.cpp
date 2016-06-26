#include "botstateresponse.h"
#include <QJsonDocument>
#include <QJsonObject>

BotStateResponse::BotStateResponse(int id, const QString& from, const QString &ip, const QString &os, BotState state)
    : Message(id, from), _ip(ip), _os(os), _state(state)
{}

void BotStateResponse::setIp(const QString& ip)
{
    _ip = ip;
}

const QString& BotStateResponse::ip() const
{
    return _ip;
}

void BotStateResponse::setOs(const QString& os)
{
    _os = os;
}

const QString& BotStateResponse::os() const
{
    return _os;
}

void BotStateResponse::setState(BotState state)
{
    _state = state;
}

BotState BotStateResponse::state() const
{
    return _state;
}

void BotStateResponse::fromJson(const QString& json)
{
    QJsonDocument document = QJsonDocument::fromJson(json.toUtf8());
    QJsonObject object = document.object();

    _id = object["id"].toInt();
    _from = object["from"].toString();
    _ip = object["ip"].toString();
    _os = object["os"].toString();
    _state = static_cast<BotState>(object["state"].toInt());
}

QString BotStateResponse::toJson() const
{
    QJsonObject object;

    object["id"] = _id;
    object["type"] = "BOT_STATE_RES";
    object["from"] = _from;
    object["ip"] = _ip;
    object["os"] = _os;
    object["state"] = static_cast<int>(_state);

    return QJsonDocument(object).toJson(QJsonDocument::Compact);
}
