
#include "events.h"

void handler_null(int ev) {}

void (*handler)(int) = &handler_null;

void install_event_handler(void (*fn)(int))
{
    handler = fn;    
}
