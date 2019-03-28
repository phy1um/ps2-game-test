#include "game.h"
#include "platform.h"
#include "ps2.h"
#include "sys.h"
#include <gsToolkit.h>

int game_enter()
{
    return 0;
}


int game_loop()
{
    GSTEXTURE test;
    gsKit_texture_bmp(gsGlobal, &test, "tiles.bmp");
    gsKit_set_clamp(gsGlobal, GS_CMODE_CLAMP);
    gsKit_set_test(gsGlobal, GS_ZTEST_OFF);
    gsKit_set_primalpha(gsGlobal, GS_SETREG_ALPHA(0,1,0,1,0), 0);
    gsGlobal->PrimAlphaEnable = GS_SETTING_ON;
    u64 black = gs_rgb(0,0,0);

    
    while(1) {
        gsKit_clear(gsGlobal, COL_CLEAR);
        gsKit_fontm_print_scaled(gsGlobal, gsFontm, 20, 20, 2, 0.5f, black, "TESTING RENDER...");
        gsKit_prim_sprite_texture(gsGlobal, &test, 
                30, 30, 0, 0, 130, 130, 100, 100,
                2, COL_NEUTRAL);
        gsKit_queue_exec(gsGlobal);
        gsKit_sync_flip(gsGlobal);
        sys_sleep(1);
    }
}
