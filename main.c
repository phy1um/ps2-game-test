#include "platform.h"
#include "sys.h"
#include "game.h"

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

    rc = game_enter();
    if(rc != 0) {
        return rc;
    }

    rc = game_loop();

    sys_shutdown();
    return rc;
}
