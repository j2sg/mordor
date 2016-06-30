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

#ifndef STORAGEMANAGER_H
#define STORAGEMANAGER_H

#include <QVariant>
#include <QString>

#define DEFAULT_SERVER "jabber.odyssey.net"

class StorageManager
{
public:
    static bool existsConfig();
    static bool createConfig(bool overwrite = false);
    static QVariant readConfig(const QString& key);
    static bool writeConfig(const QString& key, const QVariant& value);
};

#endif // STORAGEMANAGER_H
