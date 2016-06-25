#include "command.h"
#include <QJsonDocument>
#include <QJsonObject>

Command::Command(int id) : _id(id)
{}

Command::Command(const QString& json)
{
    QJsonDocument document = QJsonDocument::fromJson(json.toUtf8());
    QJsonObject object = document.object();

    _id = object["id"].toInt();
}
