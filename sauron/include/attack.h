#ifndef ATTACK_H
#define ATTACK_H

#include <QString>

class Attack
{
public:
    Attack();
    int id() const;
    const QString& target() const;
    bool inProgress() const;
    void start(const QString& target);
    void stop();
private:
    int _id;
    QString _target;
    bool _inProgress;
};

#endif // ATTACK_H
