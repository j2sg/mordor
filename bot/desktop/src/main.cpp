#include <QCoreApplication>
#include "bot.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    Bot *bot = Bot::instance();

    Q_UNUSED(bot);

    return app.exec();
}
