#ifndef GETSTATUSCOMMAND_H
#define GETSTATUSCOMMAND_H

#include "command.h"

class GetStatusCommand : public Command
{
public:
    GetStatusCommand(int id);
    GetStatusCommand(const QString& json);
    QString toJson() const;

};

#endif // GETSTATUSCOMMAND_H
