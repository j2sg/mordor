#ifndef STOPATTACKCOMMAND_H
#define STOPATTACKCOMMAND_H

#include "core_global.h"
#include "message.h"

class CORE_EXPORT StopAttackCommand : public Message
{
public:
    StopAttackCommand(int id = NO_MSG_ID, const QString& from = "", const QString& to = "");
    void fromJson(const QString& json);
    QString toJson() const;
};

#endif // STOPATTACKCOMMAND_H
