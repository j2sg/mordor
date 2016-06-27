#ifndef BOT_H
#define BOT_H

#include "types.h"
#include <QString>

class Bot
{
public:
    Bot(const QString& id = "", const QString& ip = "", const QString& os = "",
        BotState state = UndefinedState, int attackId = NO_ATTACK_ID);
    void setId(const QString& id);
    const QString& id() const;
    void setIp(const QString& ip);
    const QString& ip() const;
    void setOs(const QString& os);
    const QString& os() const;
    void setState(BotState state);
    BotState state() const;
    void setAttackId(int attackId);
    int attackId() const;
private:
    QString _id;
    QString _ip;
    QString _os;
    BotState _state;
    int _attackId;
};

#endif // BOT_H
