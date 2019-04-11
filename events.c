/**
 * common code for even handling
 */
#include "events.h"

// default no-action handler
void handler_null(int ev) {}

// default value of handler is to do nothing
void (*handler)(int) = &handler_null;

// set a new event handler
void install_event_handler(void (*fn)(int))
{
    handler = fn;    
}
