#include "message.h"
#include "getstatuscommand.h"
#include "getbotstatecommand.h"
#include "botstateresponse.h"
#include <QJsonDocument>
#include <QJsonObject>

Message::Message(int id, const QString& from) : _id(id), _from(from)
{}

void Message::setId(int id)
{
    _id = id;
}

int Message::id() const
{
    return _id;
}

void Message::setFrom(const QString& from)
{
    _from = from;
}

const QString& Message::from() const
{
    return _from;
}

Message *Message::createFromJson(const QString& json)
{
    QJsonDocument document = QJsonDocument::fromJson(json.toUtf8());
    QJsonObject object = document.object();

    Message *message = Message::createFromType(object["type"].toString());

    if(message)
        message -> fromJson(json);

    return message;
}

Message *Message::createFromType(const QString& type)
{
    if(type == "GET_STATUS_CMD")
        return new GetStatusCommand;
    else if(type == "GET_BOT_STATE_CMD")
        return new GetBotStateCommand;
    else if(type == "BOT_STATE_RES")
        return new BotStateResponse;

    return 0;
}
