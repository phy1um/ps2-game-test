/**
 * implementation of platform specific code for SDL2
 */
#include "platform.h"
#include "sys.h"

// just call out to the system shutdown
void fatal_handler(const char *msg)
{
    sys_shutdown();
}
