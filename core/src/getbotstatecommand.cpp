#include "getbotstatecommand.h"
#include <QJsonDocument>
#include <QJsonObject>

GetBotStateCommand::GetBotStateCommand(int id, const QString& from, const QString& to)
    : Message(id, from, to)
{}

void GetBotStateCommand::fromJson(const QString& json)
{
    QJsonDocument document = QJsonDocument::fromJson(json.toUtf8());
    QJsonObject documentObject = document.object();

    _id = documentObject["id"].toInt();
}

QString GetBotStateCommand::toJson() const
{
    QJsonObject documentObject;

    documentObject["id"] = _id;
    documentObject["type"] = "GET_BOT_STATE_CMD";

    return QJsonDocument(documentObject).toJson(QJsonDocument::Compact);
}
