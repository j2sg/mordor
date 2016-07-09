/**
 *  This file is part of Mordor.
 *
 *  Copyright (c) 2016 Juan Jose Salazar Garcia jjslzgc@gmail.com
 *
 *  Mordor is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Mordor is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Mordor.  If not, see <http://www.gnu.org/licenses/>.
 *
 **/

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
    QString toString() const;
private:
    int _id;
    QString _target;
};

#endif // ATTACK_H
