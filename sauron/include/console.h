#ifndef CONSOLE_H
#define CONSOLE_H

#include <QObject>

class Console : public QObject
{
    Q_OBJECT
public:
    Console(QObject *parent = 0);
signals:
    void finished();
public slots:
    void run();
private:
    bool executeCommand(const QString& command);
    void quit();
    void help();
    void createConnections();
};

#endif // CONSOLE_H
