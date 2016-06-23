#ifndef GETSTATUSCOMMAND_H
#define GETSTATUSCOMMAND_H

#include "command.h"

class GetStatusCommand : public Command
{
public:
    QString toJson() const;

};

#endif // GETSTATUSCOMMAND_H
