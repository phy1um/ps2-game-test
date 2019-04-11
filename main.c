/**
 * GS Test - a PlayStation 2 game with SDL backend
 * @author phy1um
 */
#include "platform.h"
#include "sys.h"
#include "game.h"
#include "events.h"

// setup cross-platform main definition
#if defined(__MINGW32__)
#include <windows.h>
#define MAIN() int WINAPI WinMain(HINSTANCE hI, HINSTANCE hP, LPSTR lpCmdLine, int CmdShow)
#else
#define MAIN() int main(int argc, char *argv[])
#endif

MAIN()
{
    int rc = sys_init();
    if(rc != 0) {
        return rc;
    }

    info("STARTUP");

    events_init();

    info("EVENT STARTUP");

    rc = game_enter();
    if(rc != 0) {
        return rc;
    }

    info("IN GAME, STARTING LOOP");

    rc = game_loop();

    sys_shutdown();
    return rc;
}
