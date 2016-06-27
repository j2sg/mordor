#ifndef BOTSTATERESPONSE_H
#define BOTSTATERESPONSE_H

#include "message.h"
#include "types.h"

class Bot;

class BotStateResponse : public Message
{
public:
    BotStateResponse(Bot *bot = 0, int id = NO_MSG_ID, const QString& from = "", const QString& to = "");
    BotStateResponse(const BotStateResponse& botStateResponse);
    ~BotStateResponse();
    BotStateResponse& operator=(const BotStateResponse& botStateResponse);
    void setBot(Bot *bot);
    const Bot *bot() const;
    void fromJson(const QString& json);
    QString toJson() const;
protected:
    Bot *_bot;
};

#endif // BOTSTATERESPONSE_H
