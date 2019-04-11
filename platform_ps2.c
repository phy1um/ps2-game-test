/**
 * implementation of platform specific functionality
 * @author phy1um
 */
#include "platform.h"
#include "ps2.h"
#include "video.h"

#include <stdio.h>

u64 COL_CLEAR = gs_rgb(CLEAR_R, CLEAR_G, CLEAR_B);
u64 COL_NEUTRAL = gs_rgb(0x80, 0x80, 0x80);

// go into an infinite loop, displaying the error message
void fatal_handler(const char *msg)
{
    u64 black = gs_rgb(0,0,0);
    while(1) {
        gsKit_clear(gsGlobal, COL_CLEAR);
        gsKit_fontm_print_scaled(gsGlobal, gsFontm, 20, 20, 2, 0.5f, black, msg);
        gsKit_queue_exec(gsGlobal);
        gsKit_sync_flip(gsGlobal);
        sys_sleep(100);
    }
}
