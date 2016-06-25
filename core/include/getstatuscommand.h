#ifndef GETSTATUSCOMMAND_H
#define GETSTATUSCOMMAND_H

#include "command.h"

class GetStatusCommand : public Command
{
public:
    GetStatusCommand(int id = NO_CMD_ID);
    void fromJson(const QString& json);
    QString toJson() const;
};

#endif // GETSTATUSCOMMAND_H
