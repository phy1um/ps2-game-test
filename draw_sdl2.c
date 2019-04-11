/**
 * draw implementation for SDL2
 *
 * this needs a lot of work. it currently doesn't run
 * texture loading is rough
 * integration with sdl_ttf and sdl_image is required
 *
 * @author phy1um
 * @date 2019-04-01
 */
#include <string.h>
#include <stdlib.h>
#include <SDL.h>
#include "video.h"
#include "draw.h"
#include "platform.h"

#define TEX_NAME_MAX 20
// most of our SDL state is contained in this file
static SDL_Window *window;
static SDL_Renderer *r;
static SDL_Texture **texture_list;
static int texture_max = 0;
static char **name_list;
static int *texture_free;

// clear the SDL renderer
int draw_frame_start()
{
    // Fill screen with clear colour
    SDL_SetRenderDrawColor(r, CLEAR_R, CLEAR_B, CLEAR_G, 255);
    SDL_RenderClear(r);
    return 0;
}

// TODO: draw a string from a loaded TTF font
int draw_string(const char *str, float x, float y, float scale, 
        char r, char g, char b)
{
    return 0;
}

// copy an area from a texture into our renderer
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

// present what we have drawn
int draw_frame_end()
{
    SDL_RenderPresent(r);
    return 0;
}

// setup texture memory and initialize SDL state
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
    name_list = malloc(n*TEX_NAME_MAX);
    texture_free = malloc(n*sizeof(int));
    int i;
    for(i = 0; i < n; i++) {
        // texture_free[i] = 0 => slot is free to be used
        texture_free[i] = 0;
        texture_list[i] = 0;
        memset(name_list[i], 0, TEX_NAME_MAX);
    }
    info("Allocated memory for SDL textures");
    return 0;
}

// load a texture from file
int texture_load(char *fname, const char *ref)
{
    info("Loading image %s", fname);
    // TODO: sdl_image to load from pngs like gsKit
    SDL_Surface *img = SDL_LoadBMP(fname);
    // convert surface to hw accelerated texture
    SDL_Texture *tex = SDL_CreateTextureFromSurface(r, img);
    if(tex == 0) {
        return -1;
    }
    info("Loaded image %s into texture", fname);
    // we are free to delete the surface we initially loaded into, the texutre 
    //  data is copied to the tex structure
    SDL_FreeSurface(img);

    // try to find a slot for this texture
    int i;
    for(i = 0; i < texture_max; i++) {
        if(texture_free[i]) {
            texture_free[i] = 0;
            strncpy(name_list[i], ref, TEX_NAME_MAX);
            texture_list[i] = tex;
            return 0;
        }
    }
    fatal("No room left for new textures!");
    return -1;
}

// lookup a texture by name
void *texture_get_by_name(const char *ref)
{
    dbg("Lookup texture by name: %s", ref);
    int i;
    for(i = 0; i < texture_max; i++) {
        if(!texture_free[i]) {
            if(strncmp(name_list[i], ref, TEX_NAME_MAX) == 0) {
                dbg("Found texture with name: %s", ref);
                return texture_list[i];
            }
        }
    }
    info("Could not find texture with name %s", ref);
    return 0;
}
