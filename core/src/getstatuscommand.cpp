#include "getstatuscommand.h"
#include <QJsonDocument>
#include <QJsonObject>

QString GetStatusCommand::toJson() const
{
    QJsonObject object;

    object["type"] = "GET_STATUS";

    return QJsonDocument(object).toJson(QJsonDocument::Compact);
}
