
#include "platform.h"
#include "sys.h"

void fatal_handler(const char *msg)
{
    sys_shutdown();
}
