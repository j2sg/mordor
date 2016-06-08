#include "signalmanager.h"
#include "botmanager.h"
#include <QCoreApplication>

#if defined(Q_OS_LINUX)
    void setupUnixSignals()
    {
        QVector<int> sigs;
        sigs << SIGKILL << SIGQUIT << SIGINT << SIGTERM << SIGHUP;

        foreach(int sig, sigs)
            signal(sig, unixHandler);
    }

    void unixHandler(int sig)
    {
        Q_UNUSED(sig);

        cleanup();
    }
#elif defined(Q_OS_WIN32) || defined(Q_OS_WIN64)
    void setupWindowsSignals()
    {
    }

    BOOL WINAPI windowsHandler(_In_ DWORD dwCtrlType)
    {
    }
#endif

void setupSignals()
{
    #if defined(Q_OS_LINUX)
        setupUnixSignals();
    #elif defined(Q_OS_WIN32) || defined(Q_OS_WIN64)
        setupWindowsSignals();
    #endif
}

void cleanup()
{
    BotManager *manager = BotManager::instance();

    manager -> stop();

    QCoreApplication::quit();
}
