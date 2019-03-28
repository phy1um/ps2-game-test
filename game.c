#include "game.h"
#include "platform.h"
#include "ps2.h"
#include "sys.h"
#include "draw.h"
#include "events.h"
#include <gsToolkit.h>
#include <time.h>

#define GAME_FPS 60
static unsigned long SECOND = 1000;
static unsigned long FRAME_DELTA = 1000/60;

int game_enter()
{
    init_texture_memory(5);
    int rc;
    rc = texture_load("host:res/tiles.png", "til");
    if(rc != 0) {
        fatal("Failed to load tiles.png!");
        return -1;
    }
    return 0;
}

static int buttons[EV_MAX] = {0,0,0,0};

static int x = 100;
static int y = 100;

void h(int e)
{
    buttons[e] = !buttons[e];
}

int game_loop()
{
    void *t = texture_get_by_name("til");
    if(t == 0) {
        fatal("Failed to get texture!");
        return -1;
    }
    struct sprite s = {
        t, 0, 0, 20, 20, 20, 20, 0, 0 };
    struct image im = { &s, 30, 40, 1.2f };

    unsigned long frame_end;
    unsigned long second_end = sys_time_ms() + SECOND;
    int frames = 0;
    int dx, dy;
    install_event_handler(&h);
    while(1) {
        dx = 0;
        dy = 0;
        frames++;
        frame_end = sys_time_ms() + FRAME_DELTA;
        if(buttons[EV_LEFT]) {dx = -2;}
        if(buttons[EV_RIGHT]) {dx = 2;}
        if(buttons[EV_UP]) {dy = -2;}
        if(buttons[EV_DOWN]) {dy = 2;}
        draw_frame_start();
        im.x += dx;
        im.y += dy;
        draw_string("PS2 Render Test: 0.0", 20, 30, 0.4f);
        draw_image(&im);
        draw_frame_end();
        handle_events();
        while(sys_time_ms() < frame_end) {
            sys_sleep(2);
        }
        if(sys_time_ms() > second_end) {
            second_end = sys_time_ms() + SECOND;
            info("FPS: %d", frames);
            frames = 0;
        }
    }
}
