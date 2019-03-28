#include "game.h"
#include "platform.h"
#include "ps2.h"
#include "sys.h"
#include "draw.h"
#include <gsToolkit.h>
#include <time.h>

int game_enter()
{
    return 0;
}


int game_loop()
{
    GSTEXTURE test;
    gsKit_texture_png(gsGlobal, &test, "host:res/tiles.png");
    u64 black = gs_rgb(0,0,0);
    float timedelta = 0;
    clock_t tt;

    int i = 0;
    int run = 1;
    while(run) {
        tt = clock();
        gsKit_clear(gsGlobal, COL_CLEAR);
        gsKit_fontm_print_scaled(gsGlobal, gsFontm, 20+i, 20, 2, 0.5f, black, "TEST");
        gsKit_prim_sprite_texture(gsGlobal, &test, 
                30+i, 30, 0, 0, 130, 130, 100, 100,
                2, COL_NEUTRAL);
        gsKit_queue_exec(gsGlobal);
        gsKit_sync_flip(gsGlobal);
        i++;
        sys_sleep(2);
    }
    gsKit_clear(gsGlobal, gs_rgb(100,0,0));
    gsKit_queue_exec(gsGlobal);
    gsKit_sync_flip(gsGlobal);
    return 0;
}
