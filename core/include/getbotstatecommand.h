#ifndef GETBOTSTATECOMMAND_H
#define GETBOTSTATECOMMAND_H

#include "message.h"

class GetBotStateCommand : public Message
{
public:
    GetBotStateCommand(const QString& to = "", int id = NO_MSG_ID, const QString& from = "");
    void setTo(const QString& to);
    const QString& to() const;
    void fromJson(const QString& json);
    QString toJson() const;
private:
    QString _to;
};

#endif // GETBOTSTATECOMMAND_H
