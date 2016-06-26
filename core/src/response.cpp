#include "response.h"
#include "botstateresponse.h"
#include <QJsonDocument>
#include <QJsonObject>

Response::Response(int id, const QString& from) : _id(id), _from(from)
{}

void Response::setId(int id)
{
    _id = id;
}

int Response::id() const
{
    return _id;
}

void Response::setFrom(const QString& from)
{
    _from = from;
}

const QString& Response::from() const
{
    return _from;
}

Response *Response::createFromType(const QString& type)
{
    if(type == "BOT_STATE")
        return new BotStateResponse;

    return 0;
}

Response *Response::createFromJson(const QString& json)
{
    QJsonDocument document = QJsonDocument::fromJson(json.toUtf8());
    QJsonObject object = document.object();

    return Response::createFromType(object["type"].toString());
}
