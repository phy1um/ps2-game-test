
#include "room.h"

void init_menu()
{
    struct room menu = {0};
    menu.tick = tick;
    menu.draw = draw;
    menu.load = load;
    menu.unload = unload;
    menu.enter = enter;
}

char *menu_1_entries[] = {
    "Option 1",
    "Option 2",
    "Option 3"
};


static int selection = 0;
static int in_delay = 0;
#define DELAY 5
void tick()
{
    if(in_delay > 0) {
        in_delay-=1;
        return;
    }

    if(input_pressed(EV_UP)) {
        selection -= 1;
        if(selection < 0) {
            selection = 0;
        }
        in_delay = DELAY;
    }
    else if(input_pressed(EV_DOWN)) {
        selection += 1;
        if(selection >= 3) {
            selection = 2;
        }
        in_delay = DELAY;
    }
    else if(input_pressed(EV_0)) {
        menu_action();        
    }
}

void draw()
{
    
}
