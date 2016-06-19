#include "command.h"
#include <QJsonDocument>
#include <QJsonObject>

Command::Command(CommandType type)
    : _type(type) {}

Command::Command(const QString& json)
{
    QJsonDocument document = QJsonDocument::fromJson(json.toUtf8());
    QJsonObject object = document.object();

    _type = static_cast<CommandType>(object["type"].toInt());
}

void Command::setType(CommandType type)
{
    _type = type;
}

CommandType Command::type() const
{
    return _type;
}

QString Command::toJson() const
{
    QJsonObject object;

    object["type"] = _type;

    return QJsonDocument(object).toJson(QJsonDocument::Compact);
}
