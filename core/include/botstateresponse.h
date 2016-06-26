#ifndef BOTSTATERESPONSE_H
#define BOTSTATERESPONSE_H

#include "message.h"
#include "types.h"

class BotStateResponse : public Message
{
public:
    BotStateResponse(int id = NO_MSG_ID, const QString& from = "", const QString& ip = "", const QString& os = "", BotState state = UndefinedState);
    void setIp(const QString& ip);
    const QString& ip() const;
    void setOs(const QString& os);
    const QString& os() const;
    void setState(BotState state);
    BotState state() const;
    void fromJson(const QString& json);
    QString toJson() const;
protected:
    QString _ip;
    QString _os;
    BotState _state;
};

#endif // BOTSTATERESPONSE_H
