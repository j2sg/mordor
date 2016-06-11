#include "console.h"
#include <iostream>
#include <string>
#include <QString>

Console::Console(QObject *parent) : QObject(parent)
{

}

void Console::run()
{
    std::string command;

    forever {
        std::cout << "S4ur0n> ";
        std::getline(std::cin, command);
        executeCommand(command.data());
    }
}

bool Console::executeCommand(const QString& command)
{
    if(command == "quit") {
        std::cout << "Bye!!" << std::endl;
        quit();
    }

    return true;
}

void Console::quit()
{
    emit finished();
}

void Console::createConnections()
{

}
