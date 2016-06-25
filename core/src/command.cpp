#include "command.h"
#include "getstatuscommand.h"
#include <QJsonDocument>
#include <QJsonObject>

Command::Command(int id) : _id(id)
{}

void Command::setId(int id)
{
    _id = id;
}

int Command::id() const
{
    return _id;
}

Command *Command::createFromType(const QString& type)
{
    if(type == "GET_STATUS")
        return new GetStatusCommand;

    return 0;
}

Command *Command::createFromJson(const QString& json)
{
    QJsonDocument document = QJsonDocument::fromJson(json.toUtf8());
    QJsonObject object = document.object();

    return Command::createFromType(object["type"].toString());
}
