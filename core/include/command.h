#ifndef COMMAND_H
#define COMMAND_H

#include <QString>

class Command
{
public:
    virtual QString toJson() const = 0;
};

#endif // COMMAND_H
