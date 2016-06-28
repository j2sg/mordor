#include "startattackcommand.h"
#include <QJsonDocument>
#include <QJsonObject>

StartAttackCommand::StartAttackCommand(const QString& target, int id, const QString& from, const QString& to)
    : Message(id, from, to), _target(target)
{}

void StartAttackCommand::setTarget(const QString& target)
{
    _target = target;
}

const QString& StartAttackCommand::target() const
{
    return _target;
}

void StartAttackCommand::fromJson(const QString& json)
{
    QJsonDocument document = QJsonDocument::fromJson(json.toUtf8());
    QJsonObject documentObject = document.object();

    _id = documentObject["id"].toInt();
    _target = documentObject["target"].toString();
}

QString StartAttackCommand::toJson() const
{
    QJsonObject documentObject;

    documentObject["id"] = _id;
    documentObject["type"] = "START_ATTACK_CMD";
    documentObject["target"] = _target;

    return QJsonDocument(documentObject).toJson(QJsonDocument::Compact);
}
