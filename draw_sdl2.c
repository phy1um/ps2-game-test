
#include <string.h>
#include <stdlib.h>
#include <SDL.h>
#include "video.h"
#include "draw.h"
#include "platform.h"

static SDL_Window *window;
static SDL_Renderer *r;
static SDL_Texture **texture_list;
static int texture_max = 0;
static char **name_list;
static int *texture_free;

int draw_frame_start()
{
    // Fill screen with clear colour
    SDL_SetRenderDrawColor(r, CLEAR_R, CLEAR_B, CLEAR_G, 255);
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
    return 0;
}

int draw_frame_end()
{
    SDL_RenderPresent(r);
    return 0;
}

int init_texture_memory(size_t n)
{
    window = SDL_CreateWindow("Test Game", 0, 0, VIDEO_WIDTH, VIDEO_HEIGHT, 0);
    if(window == 0) {
        fatal("Failed to create SDL window");
        return -1;
    }
    r = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    info("Created SDL window and renderer");

    texture_max = n;
    texture_list = malloc(n*sizeof(SDL_Texture*));
    name_list = malloc(n*20);
    texture_free = malloc(n*sizeof(int));
    int i;
    for(i = 0; i < n; i++) {
        texture_free[i] = 0;
        texture_list[i] = 0;
        memset(name_list[i], 0, 20);
    }
    info("Allocated memory for SDL textures");
    return 0;
}

int texture_load(char *fname, const char *ref)
{
    info("Loading image %s", fname);
    SDL_Surface *img = SDL_LoadBMP(fname);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(r, img);
    if(tex == 0) {
        return -1;
    }
    info("Loaded image %s into texture", fname);
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
    dbg("Lookup texture by name: %s", ref);
    int i;
    for(i = 0; i < texture_max; i++) {
        if(!texture_free[i]) {
            if(strncmp(name_list[i], ref, 20) == 0) {
                dbg("Found texture with name: %s", ref);
                return texture_list[i];
            }
        }
    }
    info("Could not find texture with name %s", ref);
    return 0;
}
