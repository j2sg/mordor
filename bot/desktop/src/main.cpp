#include <QCoreApplication>
#include <iostream>
#include "bot.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    Bot *bot = Bot::instance();

    if(argc != 3) {
        std::cout << argv[0] << " <jid> <password>" << std::endl;
        return 1;
    }

    bot -> connectToServer(argv[1], argv[2]);

    return app.exec();
}
