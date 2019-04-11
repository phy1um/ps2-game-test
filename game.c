/**
 * platform-independent implementation of main game loop
 *
 * @author phy1um
 * @date 2019-03-20
 */
#include "game.h"
#include "platform.h"
#include "sys.h"
#include "draw.h"
#include "events.h"
#include "input.h"
#include "room.h"
#include "rooms/room_list.h"

// how many frames per second do we update and draw at
#define GAME_FPS 60
static unsigned long SECOND = 1000;
static unsigned long FRAME_DELTA = 1000/60;

// current menu bound to the game
static struct menu *menu_target;
// 1 if we are in the menu else 0
static int in_menu;
// which menu index do we have currently selected
static int menu_selection;

void do_menu_logic()
{
    size_t max = menu_target->entry_count;
    if(input_pressed(EV_0)) {
        if(menu_selection >= 0 && menu_selection < max) {
            menu_target->actions[menu_selection]();
        }
    }
    else if(input_pressed(EV_DOWN)) {
        menu_selection += 1;
        if(menu_selection >= max) {
            menu_selection = 0;
        }
    }
    else if(input_pressed(EV_UP)) {
        menu_selection -= 1;
        if(menu_selection < 0) {
            menu_selection = max - 1;
        }
    }
    else if(input_pressed(EV_START)) {
        game_menu_off();
    }

    if(menu_target->pause_ticks == 0) {
        room_tick();
    }
    if(menu_target->draw_over) {
        room_draw();
    }
    if(menu_target->draw) {
        menu_target->draw();
    }
    else {
        size_t i;
        for(i = 0; i < menu_target->entry_count; i++) {
            if(menu_selection == i) {
                draw_string(menu_target->options[i], 40, 30 + (30*i), 
                        0.9, 255, 0, 0);
            }
            else {
                draw_string(menu_target->options[i], 40, 30 + (30*i), 
                        0.9, 0, 0, 0);
            }
        }
    }
}

int game_set_menu(struct menu *m)
{
    menu_target = m;
}

int game_menu_on()
{
    in_menu = 1;
    menu_selection = 0;
}

int game_menu_off()
{
    in_menu = 0;
}

//call other initialisation functions and setup the default room
int game_enter()
{
    info("Initializing texture memory for 5 textures");
    init_texture_memory(5);
    info("Initializing input");
    input_init();
    info("Setting up SANDBOX room to run");
    int r = room_bind(get_sandbox_room());
    if(r < 0) {
        fatal("Failed to init sandbox room!");
        return -1;
    }
    info("Loading room...");
    room_load(r);
    info("Entering room");
    room_enter(r);
    return 0;
}

// run the main game loop forever (or until it breaks)
int game_loop()
{
    unsigned long frame_end;
    unsigned long second_end = sys_time_ms() + SECOND;
    int frames = 0;
    while(1) {
        // count frames each second
        frames++;
        // what time do we expect this frame to end
        frame_end = sys_time_ms() + FRAME_DELTA;
        input_frame_begin();
        handle_events();
        draw_frame_start();
        if(in_menu) {
            do_menu_logic();
        }
        else {
            draw_string("PS2 Render Test: 0.0.0", 15, 15, 0.2f, 0, 0, 0);
            room_draw();
            room_tick();
        }
        draw_frame_end();
        // wait until the frame is over if we have spare time
        while(sys_time_ms() < frame_end) {
            sys_sleep(2);
        }
        // every second report our FPS
        if(sys_time_ms() > second_end) {
            second_end = sys_time_ms() + SECOND;
            info("FPS: %d", frames);
            frames = 0;
        }
    }
}
