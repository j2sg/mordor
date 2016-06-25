#ifndef COMMAND_H
#define COMMAND_H

#include <QString>

#define NO_CMD_ID -1

class Command
{
public:
    Command(int id);
    virtual ~Command() {}
    void setId(int id);
    int id() const;
    static Command *createFromType(const QString& type);
    static Command *createFromJson(const QString& json);
    virtual void fromJson(const QString& json) = 0;
    virtual QString toJson() const = 0;
protected:
    int _id;
};

#endif // COMMAND_H
