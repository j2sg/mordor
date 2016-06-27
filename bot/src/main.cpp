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
