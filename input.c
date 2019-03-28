
#include "events.h"
#include "platform.h"

static int button_held[EV_MAX];
static int button_pressed[EV_MAX];
static int button_released[EV_MAX];

#define testid(i) do {\
    if(i < 0 || i >= EV_MAX) { fatal("Invalid button ID %d tested", i); }\
    }while(0)

int input_held(int button)
{
    testid(button);
    return button_held[button];
}

int input_pressed(int button)
{
    testid(button);
    return button_pressed[button];
}

int input_released(int button)
{
    testid(button);
    return button_released[button];
}

void input_handler(int button)
{
    testid(button);
    button_held[button] = !button_held[button];
    if(button_held[button]) {
        button_pressed[button] = 1;
    }
    else {
        button_released[button]= 1;
    }
}

void input_frame_begin()
{
    int i;
    for(i = 0; i < EV_MAX; i++) {
        button_pressed[i] = 0;
        button_released[i] = 0;
    }
}

void input_init()
{
    install_event_handler(&input_handler);
    input_frame_begin();
    int i;
    for(i = 0; i < EV_MAX; i++) {
        button_held[i] = 0;
    }
}


