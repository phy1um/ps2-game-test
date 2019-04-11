/**
 * abstract event handlers, and abstracting buttons into EV_X commands
 *
 * @author phy1um
 * @date 2019-03-30
 */
#ifndef PS2_INPUT_H__
#define PS2_INPUT_H__

#define EV_LEFT 1
#define EV_RIGHT 2
#define EV_UP 3
#define EV_DOWN 4
#define EV_0 5
#define EV_1 6
#define EV_2 7
#define EV_3 8
#define EV_4 9
#define EV_START 10
#define EV_SELECT 11
#define EV_MAX 11

/**
 * must be called before any events can be handled
 */
void events_init();

/**
 * a handler which deals with event logic in some context
 */
extern void (*handler)(int event);

/**
 * setup a different handler for events, for some different context
 * @param fn the new handler function
 */
void install_event_handler(void(*fn)(int));

/**
 * call this each frame to get events and pass them into the current handler
 */
void handle_events();

#endif
