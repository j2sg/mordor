#include "getstatuscommand.h"
#include <QJsonDocument>
#include <QJsonObject>

GetStatusCommand::GetStatusCommand(int id, const QString& from) : Message(id, from)
{}

void GetStatusCommand::fromJson(const QString& json)
{
    QJsonDocument document = QJsonDocument::fromJson(json.toUtf8());
    QJsonObject object = document.object();

    _id = object["id"].toInt();
    _from = object["from"].toString();
}

QString GetStatusCommand::toJson() const
{
    QJsonObject object;

    object["id"] = _id;
    object["type"] = "GET_STATUS_CMD";
    object["from"] = _from;

    return QJsonDocument(object).toJson(QJsonDocument::Compact);
}
