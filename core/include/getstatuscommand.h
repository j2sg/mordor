#ifndef GETSTATUSCOMMAND_H
#define GETSTATUSCOMMAND_H

#include "message.h"

class GetStatusCommand : public Message
{
public:
    GetStatusCommand(int id = NO_MSG_ID, const QString& from = "");
    void fromJson(const QString& json);
    QString toJson() const;
};

#endif // GETSTATUSCOMMAND_H
