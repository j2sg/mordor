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
        quit();
    } else if(command == "help") {
        help();
    } else {
        return false;
    }

    return true;
}

void Console::quit()
{
    std::cout << "Bye!!" << std::endl;

    emit finished();
}

void Console::help()
{
    std::cout << "\tLista de comandos" << std::endl;
    std::cout << "\t=================" << std::endl << std::endl;
    std::cout << "\tComando\t\tDescripcion" << std::endl;
    std::cout << "\t=======\t\t===========" << std::endl << std::endl;
    std::cout << "\tquit\t\tSalir" << std::endl;
    std::cout << "\thelp\t\tMostrar Ayuda" << std::endl;
    std::cout << std::endl;
}

void Console::createConnections()
{

}
