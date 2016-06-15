#include <QCoreApplication>
#include "signalmanager.h"
#include "botmanager.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    setupSignals();

    BotManager *manager = BotManager::instance();

    manager -> start();

    return app.exec();
}
