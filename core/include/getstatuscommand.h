#ifndef GETSTATUSCOMMAND_H
#define GETSTATUSCOMMAND_H

#include "core_global.h"
#include "message.h"

class CORE_EXPORT GetStatusCommand : public Message
{
public:
    GetStatusCommand(int id = NO_MSG_ID, const QString& from = "", const QString& to = "");
    void fromJson(const QString& json);
    QString toJson() const;
};

#endif // GETSTATUSCOMMAND_H
