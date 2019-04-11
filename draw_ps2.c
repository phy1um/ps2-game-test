/**
 * draw implementation for the playstation 2 console
 *
 * @author phy1um
 * @date 2019-03-23
 */

#include <gsToolkit.h>
#include "draw.h"
#include "platform.h"
#include "ps2.h"

u64 black = gs_rgb(0,0,0);
u64 white = gs_rgb(0xff, 0xff, 0xff);

/**
 * memory for managing texture loading
 */
struct texload {
    int used;
    GSTEXTURE tex;
    char name[10];
};

#define TEX_LOAD_MAX 5

// we pre-allocate texture memory, as there is no reason to do this dynamically
//  in a console environment
static struct texload textures[TEX_LOAD_MAX];

// 1 when we are in a frame else 0, used for warnings and status tracking
static int in_frame = 0;

// clear the gs
int draw_frame_start()
{
    gsKit_clear(gsGlobal, COL_CLEAR);    
    in_frame = 1;
    return 0;
}

// execute the gs queue and flip buffers
int draw_frame_end()
{
   gsKit_queue_exec(gsGlobal);
   gsKit_sync_flip(gsGlobal);
   in_frame = 0;
   return 0;
}

// use the default gsKit font to display a string at fixed depth 2
int draw_string(const char *str, float x, float y, float scale, char r, char g, char b)
{
#ifdef DEBUG
    if(in_frame == 0) {
        error("Drawing out of frame");
    }
#endif
    u64 col = gs_rgb(r,g,b);
    gsKit_fontm_print_scaled(gsGlobal, gsFontm, x, y, 2, scale, col, str);
    return 0;
}

// draw a textured quad at fixed depth 2
//  blending with COL_NEUTRAL gives the exact pixels from the texture
int draw_image(const struct image *img)
{
    gsKit_prim_sprite_texture(gsGlobal, (GSTEXTURE*)img->tgt->texture, 
            img->x, img->y, img->tgt->u1, img->tgt->v1,
            img->x + img->tgt->w, img->y + img->tgt->h,
            img->tgt->u2, img->tgt->v2, 2, COL_NEUTRAL);
    return 0;
}

// perform some general gsKit initialisation, cleanup our texture memory
int init_texture_memory(size_t n)
{
    gsKit_set_clamp(gsGlobal, GS_CMODE_CLAMP);
    // disable depth tests, everything is the same depth in our 2d world
    gsKit_set_test(gsGlobal, GS_ZTEST_OFF);
    // setup transparency (important for font drawing)
    gsKit_set_primalpha(gsGlobal, GS_SETREG_ALPHA(0,1,0,1,0), 0);
    gsGlobal->PrimAlphaEnable = GS_SETTING_ON;

    int i;
    for(i = 0; i < TEX_LOAD_MAX; i++) {
        textures[i].used = 0;
        textures[i].name[0] = 0;
    }
    return 0;
}

// load a texture with gsKit functions
int texture_load(char *fname, const char *ref)
{
    int i;
    for(i = 0; i < TEX_LOAD_MAX; i++) {
        if(textures[i].used == 0) {
            gsKit_texture_png(gsGlobal, &textures[i].tex, fname);
            textures[i].used = 1;
            strncpy(textures[i].name, ref, 10);
            return 0;
        }
    }
    return -1;
}

// search for a loaded texture and return it
void *texture_get_by_name(const char *ref)
{
    int i;
    for(i = 0; i < TEX_LOAD_MAX; i++) {
        if(textures[i].used == 1) {
            if( strncmp(textures[i].name, ref, 10) == 0 ) {
                return (void *) &textures[i].tex;
            }
        }
    }
    return 0;
}


