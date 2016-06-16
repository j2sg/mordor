#ifndef BOT_H
#define BOT_H

#include "types.h"
#include <QString>

class Bot
{
public:
    Bot(const QString& id, const QString& ip, const QString& os, BotState state = WaitingForCommand);
    const QString& id() const;
    const QString& ip() const;
    const QString& os() const;
    void setState(BotState state);
    BotState state() const;
private:
    QString _id;
    QString _ip;
    QString _os;
    BotState _state;
};

#endif // BOT_H
