#ifndef BOT_H
#define BOT_H

#include "core_global.h"
#include "types.h"
#include "attack.h"
#include <QString>

class CORE_EXPORT Bot
{
public:
    Bot(const QString& id = "", const QString& ip = "", const QString& os = "",
        BotState state = UndefinedState, const Attack& attack = Attack());
    void setId(const QString& id);
    const QString& id() const;
    void setIp(const QString& ip);
    const QString& ip() const;
    void setOs(const QString& os);
    const QString& os() const;
    void setState(BotState state);
    BotState state() const;
    void setAttack(const Attack& attack);
    const Attack& attack() const;
private:
    QString _id;
    QString _ip;
    QString _os;
    BotState _state;
    Attack _attack;
};

#endif // BOT_H
