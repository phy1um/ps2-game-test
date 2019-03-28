
#include <string.h>
#include <SDL.h>
#include "video.h"

static SDL_Renderer *r;
static SDL_Texture **texture_list;
static int texture_max = 0;
static char **name_list;

int draw_frame_start()
{
    // Fill screen with clear colour
    SDL_SetRendererDrawColor(r, CLEAR_R, CLEAR_B, CLEAR_G, 255);
    SDL_RenderClear(r);
    return 0;
}

int draw_string(const char *str, float x, float y, float scale, 
        char r, char g, char b)
{
    return 0;
}

int draw_image(const struct image *img)
{
    SDL_Rect from;
    SDL_Rect to;
    // Area of image being drawn
    to.x = img->x;
    to.y = img->y;
    to.w = img->tgt->w;
    to.h = img->tgt->h;
    // Area on texture
    from.x = img->tgt->u1;
    from.y = img->tgt->v1;
    from.w = img->tgt->u2;
    from.h = img->tgt->v2;

    SDL_RenderCopy(r, img->tgt->texture, &from, &to);
}

int draw_frame_end()
{
    SDL_RenderPresent(r);
}

int init_texture_memory(size_t n)
{
    texture_max = n;
    texture_list = malloc(n*sizeof(SDL_Texture*));
    name_list = malloc(n*20);
}

int texture_load(char *fname, const char *ref)
{
    SDL_Surface *img = SDL_LoadBMP(fname);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(r, img);
    SDL_FreeSurface(img);
    int i;
    for(i = 0; i < texture_max; i++) {
        if(texture_free[i]) {
            texture_free[i] = 0;
            strncpy(name_list[i], ref, 20);
            texture_list[i] = tex;
            return 0;
        }
    }
    fatal("No room left for new textures!");
    return -1;
}

void *texture_get_by_name(const char *ref)
{
    int i;
    for(i = 0; i < texture_max; i++) {
        if(!texture_free[i]) {
            if(strncpy(name_list[i], ref, 20) == 0) {
                return texture_list[i];
            }
        }
    }
    return 0;
}
