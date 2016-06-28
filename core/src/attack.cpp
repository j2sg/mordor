#include "attack.h"

Attack::Attack(int id, const QString& target)
    : _id(id), _target(target)
{}

void Attack::setId(int id)
{
    _id = id;
}

int Attack::id() const
{
    return _id;
}

void Attack::setTarget(const QString& target)
{
    _target = target;
}

const QString& Attack::target() const
{
    return _target;
}
