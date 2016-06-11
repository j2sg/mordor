#include <QCoreApplication>
#include "console.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    Console console;

    QObject::connect(&console, SIGNAL(finished()), &app, SLOT(quit()));

    console.run();

    return app.exec();
}
