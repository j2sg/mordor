#ifndef STARTATTACKCOMMAND_H
#define STARTATTACKCOMMAND_H

#include "core_global.h"
#include "message.h"

class CORE_EXPORT StartAttackCommand : public Message
{
public:
    StartAttackCommand(const QString& target = "", int id = NO_MSG_ID, const QString& from = "", const QString& to = "");
    void setTarget(const QString& target);
    const QString& target() const;
    void fromJson(const QString& json);
    QString toJson() const;
private:
    QString _target;
};

#endif // STARTATTACKCOMMAND_H
