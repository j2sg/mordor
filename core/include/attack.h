#ifndef ATTACK_H
#define ATTACK_H

#include <QString>
#include <QDateTime>

class Attack {
public:
    Attack(int id, const QDateTime& start, int bots = 0);
    int id() const;
    const QDateTime& start() const;
    int bots() const;
private:
    int _id;
    QDateTime _start;
    int _bots;
};


#endif // ATTACK_H
