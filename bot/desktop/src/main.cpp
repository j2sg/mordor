#include <QCoreApplication>
#include "botmanager.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    BotManager *manager = BotManager::instance();

    manager -> start();

    return app.exec();
}
