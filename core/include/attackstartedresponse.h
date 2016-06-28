#ifndef ATTACKSTARTEDRESPONSE_H
#define ATTACKSTARTEDRESPONSE_H

#include "core_global.h"
#include "message.h"

class CORE_EXPORT AttackStartedResponse : public Message
{
public:
    AttackStartedResponse(int id = NO_MSG_ID, const QString& from = "", const QString& to = "");
    void fromJson(const QString& json);
    QString toJson() const;
};

#endif // ATTACKSTARTEDRESPONSE_H
