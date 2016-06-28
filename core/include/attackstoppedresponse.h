#ifndef ATTACKSTOPPEDRESPONSE_H
#define ATTACKSTOPPEDRESPONSE_H

#include "core_global.h"
#include "message.h"

class CORE_EXPORT AttackStoppedResponse : public Message
{
public:
    AttackStoppedResponse(int id = NO_MSG_ID, const QString& from = "", const QString& to = "");
    void fromJson(const QString& json);
    QString toJson() const;
};

#endif // ATTACKSTOPPEDRESPONSE_H
