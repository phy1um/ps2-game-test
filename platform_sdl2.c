
#include "platform.h"

void fatal_handler(const char *msg)
{
    sys_shutdown();
}
