#ifndef SIGNALMANAGER_H
#define SIGNALMANAGER_H

#include <QVector>

#if defined(Q_OS_LINUX)
    #include <signal.h>

    void setupUnixSignals();
    void unixHandler(int sig);
#elif defined(Q_OS_WIN32) || defined(Q_OS_WIN64)
    #include <windows.h>

    void setupWindowsSignals();
    BOOL WINAPI windo   wsHandler(_In_ DWORD dwCtrlType);
#endif

void setupSignals();
void cleanup();

#endif // SIGNALMANAGER_H
