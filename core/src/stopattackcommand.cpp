#include "stopattackcommand.h"
#include <QJsonDocument>
#include <QJsonObject>

StopAttackCommand::StopAttackCommand(int id, const QString& from, const QString& to)
    : Message(id, from, to)
{}

void StopAttackCommand::fromJson(const QString& json)
{
    QJsonDocument document = QJsonDocument::fromJson(json.toUtf8());
    QJsonObject documentObject = document.object();

    _id = documentObject["id"].toInt();
}

QString StopAttackCommand::toJson() const
{
    QJsonObject documentObject;

    documentObject["id"] = _id;
    documentObject["type"] = "STOP_ATTACK_CMD";

    return QJsonDocument(documentObject).toJson(QJsonDocument::Compact);
}
