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

extern void (*handler)(int event);
void install_event_handler(void(*fn)(int));
void handle_events();

#endif
