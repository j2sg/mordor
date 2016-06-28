#ifndef GETBOTSTATECOMMAND_H
#define GETBOTSTATECOMMAND_H

#include "core_global.h"
#include "message.h"

class CORE_EXPORT GetBotStateCommand : public Message
{
public:
    GetBotStateCommand(int id = NO_MSG_ID, const QString& from = "", const QString& to = "");
    void fromJson(const QString& json);
    QString toJson() const;
};

#endif // GETBOTSTATECOMMAND_H
