#include "attack.h"

Attack::Attack() : _id(0), _target(""), _inProgress(false)
{}

int Attack::id() const
{
    return _id;
}

const QString& Attack::target() const
{
    return _target;
}

bool Attack::inProgress() const
{
    return _inProgress;
}

void Attack::start(const QString& target)
{
    if(_inProgress)
        return;

    ++_id;
    _target = target;
    _inProgress = true;
}

void Attack::stop()
{
    if(!_inProgress)
        return;

    _target = "";
    _inProgress = false;
}
