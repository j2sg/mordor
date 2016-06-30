#ifndef ATTACK_H
#define ATTACK_H

#include "core_global.h"
#include <QString>

#define NO_ATTACK_ID 0

class CORE_EXPORT Attack
{
public:
    Attack(int id = NO_ATTACK_ID, const QString& target = "");
    void setId(int id);
    int id() const;
    void setTarget(const QString& target);
    const QString& target() const;
private:
    int _id;
    QString _target;
};

#endif // ATTACK_H
