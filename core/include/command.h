#ifndef COMMAND_H
#define COMMAND_H

#include <QString>

class Command
{
public:
    Command(int id);
    Command(const QString& json);
    virtual QString toJson() const = 0;
private:
    int _id;
};

#endif // COMMAND_H
