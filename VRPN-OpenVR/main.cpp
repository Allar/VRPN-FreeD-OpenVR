#include <windows.h>
#include <memory>
#include "vrpn_Server_OpenVR.h"

static volatile int done = 0;
std::unique_ptr<vrpn_Server_OpenVR> server{};

// install a signal handler to shut down the devices
// On Windows, the signal handler is run in a different thread from
// the main application.  We don't want to go destroying things in
// here while they are being used there, so we set a flag telling the
// main program it is time to exit.
#if defined(_WIN32) && !defined(__CYGWIN__)
/**
* Handle exiting cleanly when we get ^C or other signals.
*/
BOOL WINAPI handleConsoleSignalsWin(DWORD signaltype)
{
    switch (signaltype) {
    case CTRL_C_EVENT:
    case CTRL_BREAK_EVENT:
    case CTRL_CLOSE_EVENT:
    case CTRL_SHUTDOWN_EVENT:
        done = 1;
        return TRUE;
        // Don't exit, but return FALSE so default handler
        // gets called. The default handler, ExitProcess, will exit.
    default:
        return FALSE;
    }
}
#endif

#define WS_VER_MAJOR 2
#define WS_VER_MINOR 2

int main(int argc, char *argv[]) {
#if 0
    // init winsock
    WSADATA wsaData;
    WSAStartup
    (
        ((unsigned long)WS_VER_MAJOR) |
        (((unsigned long)WS_VER_MINOR) << 8),
        &wsaData
    );
#endif
    server = std::make_unique<vrpn_Server_OpenVR>(argc, argv);
    while (!done) {
        server->mainloop();
        vrpn_SleepMsecs(server->sleep_interval);
    }
    server.reset(nullptr);
    return 0;
}