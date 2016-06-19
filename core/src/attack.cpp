#include "attack.h"

Attack::Attack(int id, const QDateTime& start, int bots)
    : _id(id), _start(start), _bots(bots) {}

int Attack::id() const
{
    return _id;
}

const QDateTime& Attack::start() const
{
    return _start;
}

int Attack::bots() const
{
    return _bots;
}
