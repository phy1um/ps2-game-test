#include "game.h"
#include "platform.h"
#include "ps2.h"
#include "sys.h"
#include "draw.h"
#include <gsToolkit.h>
#include <time.h>

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

    while(1) {
        draw_frame_start();
        im.x += 1;
        draw_string("PS2 Render Test: 0.0", 5, 8, 0.9f);
        draw_image(&im);
        draw_frame_end();
        sys_sleep(2);
    }
}
