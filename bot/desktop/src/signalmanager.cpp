#include "signalmanager.h"

#if defined(Q_OS_LINUX)
    void setupUnixSignals()
    {
    }

    void unixHandler(int sig)
    {
    }
#elif defined(Q_OS_WIN32) || defined(Q_IS_WIN64)
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
    #elif defined(Q_OS_WIN32) || defined(Q_IS_WIN64)
        setupWindowsSignals();
    #endif
}

void cleanup()
{
}
