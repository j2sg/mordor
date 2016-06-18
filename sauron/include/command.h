#ifndef COMMAND_H
#define COMMAND_H

#include "types.h"
#include <QString>

class Command
{
public:
    Command(CommandType type);
    Command(const QString& json);
    void setType(CommandType type);
    CommandType type() const;
    QString toJson() const;
private:
    CommandType _type;
};

#endif // COMMAND_H
