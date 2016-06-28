#include "attackstartedresponse.h"
#include <QJsonDocument>
#include <QJsonObject>

AttackStartedResponse::AttackStartedResponse(int id, const QString& from, const QString& to)
    : Message(id, from, to)
{}

void AttackStartedResponse::fromJson(const QString& json)
{
    QJsonDocument document = QJsonDocument::fromJson(json.toUtf8());
    QJsonObject documentObject = document.object();

    _id = documentObject["id"].toInt();
}

QString AttackStartedResponse::toJson() const
{
    QJsonObject documentObject;

    documentObject["id"] = _id;
    documentObject["type"] = "ATTACK_STARTED_RES";

    return QJsonDocument(documentObject).toJson(QJsonDocument::Compact);
}
