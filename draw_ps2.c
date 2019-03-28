
#include <gsToolkit.h>
#include "draw.h"
#include "platform.h"
#include "ps2.h"

u64 black = gs_rgb(0,0,0);
u64 white = gs_rgb(0xff, 0xff, 0xff);

struct texload {
    int used;
    GSTEXTURE tex;
    char name[10];
};

#define TEX_LOAD_MAX 5

static struct texload textures[TEX_LOAD_MAX];

static int in_frame = 0;

int draw_frame_start()
{
    gsKit_clear(gsGlobal, COL_CLEAR);    
    in_frame = 1;
    return 0;
}

int draw_frame_end()
{
   gsKit_queue_exec(gsGlobal);
   gsKit_sync_flip(gsGlobal);
   in_frame = 0;
   return 0;
}

int draw_string(const char *str, float x, float y, float scale)
{
#ifdef DEBUG
    if(in_frame == 0) {
        error("Drawing out of frame");
    }
#endif
    gsKit_fontm_print_scaled(gsGlobal, gsFontm, x, y, 2, scale, black, str);
    return 0;
}

int draw_image(const struct image *img)
{
    gsKit_prim_sprite_texture(gsGlobal, (GSTEXTURE*)img->tgt->texture, 
            img->x, img->y, img->tgt->u1, img->tgt->v1,
            img->x + img->tgt->w, img->y + img->tgt->h,
            img->tgt->u2, img->tgt->v2, 2, COL_NEUTRAL);
    return 0;
}


int init_texture_memory(size_t n)
{
    gsKit_set_clamp(gsGlobal, GS_CMODE_CLAMP);
    gsKit_set_test(gsGlobal, GS_ZTEST_OFF);
    gsKit_set_primalpha(gsGlobal, GS_SETREG_ALPHA(0,1,0,1,0), 0);
    gsGlobal->PrimAlphaEnable = GS_SETTING_ON;

    int i;
    for(i = 0; i < TEX_LOAD_MAX; i++) {
        textures[i].used = 0;
        textures[i].name[0] = 0;
    }
    return 0;
}

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


