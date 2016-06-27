#include "getbotstatecommand.h"
#include <QJsonDocument>
#include <QJsonObject>

GetBotStateCommand::GetBotStateCommand(const QString& to, int id, const QString& from)
    : Message(id, from), _to(to)
{}

void GetBotStateCommand::GetBotStateCommand::setTo(const QString& to)
{
    _to = to;
}

const QString& GetBotStateCommand::GetBotStateCommand::to() const
{
    return _to;
}

void GetBotStateCommand::fromJson(const QString& json)
{
    QJsonDocument document = QJsonDocument::fromJson(json.toUtf8());
    QJsonObject documentObject = document.object();

    _id = documentObject["id"].toInt();
    _to = documentObject["to"].toString();
}

QString GetBotStateCommand::toJson() const
{
    QJsonObject documentObject;

    documentObject["id"] = _id;
    documentObject["type"] = "GET_BOT_STATE_CMD";
    documentObject["to"] = _to;

    return QJsonDocument(documentObject).toJson(QJsonDocument::Compact);
}
