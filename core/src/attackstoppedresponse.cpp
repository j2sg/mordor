#include "attackstoppedresponse.h"
#include <QJsonDocument>
#include <QJsonObject>

AttackStoppedResponse::AttackStoppedResponse(int id, const QString& from, const QString& to)
    : Message(id, from, to)
{}

void AttackStoppedResponse::fromJson(const QString& json)
{
    QJsonDocument document = QJsonDocument::fromJson(json.toUtf8());
    QJsonObject documentObject = document.object();

    _id = documentObject["id"].toInt();
}

QString AttackStoppedResponse::toJson() const
{
    QJsonObject documentObject;

    documentObject["id"] = _id;
    documentObject["type"] = "ATTACK_STOPPED_RES";

    return QJsonDocument(documentObject).toJson(QJsonDocument::Compact);
}
