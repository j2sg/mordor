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

#include "storagemanager.h"
#include <QSettings>
#include <QFile>
#include <QTextStream>

bool StorageManager::existsConfig()
{
    QSettings setting("config.ini", QSettings::IniFormat);

    return setting.value("Executed", false).toBool();
}

bool StorageManager::createConfig(bool overwrite)
{
    if(existsConfig() && !overwrite)
        return false;

    QSettings setting("config.ini", QSettings::IniFormat);

    setting.setValue("Executed", true);
    setting.setValue("jid",      "");
    setting.setValue("password", "");

    return true;
}

QVariant StorageManager::readConfig(const QString& key)
{
    if(!existsConfig())
        return QVariant();

    QSettings setting("config.ini", QSettings::IniFormat);

    return setting.value(key);
}

bool StorageManager::writeConfig(const QString& key, const QVariant& value)
{
    if(!existsConfig())
        return false;

    QSettings setting("config.ini", QSettings::IniFormat);

    if(!setting.contains(key))
        return false;

    setting.setValue(key, value);

    return true;
}

QStringList StorageManager::readServerList()
{
    QFile file(SERVER_LIST_FILE);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return QStringList();

    QStringList servers;
    QTextStream stream(&file);

    while(!stream.atEnd())
        servers << stream.readLine();

    return servers;
}
