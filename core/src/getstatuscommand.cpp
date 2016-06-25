#include "getstatuscommand.h"
#include <QJsonDocument>
#include <QJsonObject>

GetStatusCommand::GetStatusCommand(int id) : Command(id)
{}

GetStatusCommand::GetStatusCommand(const QString& json) : Command(json)
{}

QString GetStatusCommand::toJson() const
{
    QJsonObject object;

    object["id"] = _id;
    object["type"] = "GET_STATUS";

    return QJsonDocument(object).toJson(QJsonDocument::Compact);
}
