/**
 * simple platform-independent sprite-sheet drawing to quads
 *
 * @author phy1um
 * @date 2019-04-01
 */
#ifndef PS2_DRAW_H__
#define PS2_DRAW_H__

#include <stdlib.h>

/**
 * a region of a texture
 */
struct sprite {
    // a pointer to memory representing some texture
    void *texture;
    // coordinates in texture to draw from
    float u1;
    float v1;
    float u2;
    float v2;
    // width and height of target quad
    float w;
    float h;
    // natural sprite offset (usually 0)
    float offset_x;
    float offset_y;
};

/**
 * an instance of a sprite which has a location in the world
 */
struct image {
    struct sprite *tgt;
    float x;
    float y;
    float scale;
};

/**
 * called at the start of each frame before any drawing
 *
 * this function should cleanup the screen, setup buffers and memory, etc
 * @returns 0 on success, nonzero on failure
 */
int draw_frame_start();

/**
 * draw a coloured string to a given position of the screen in some default font
 * @returns 0 on success, nonzero on failure
 */
int draw_string(const char *str, float x, float y, float scale, 
        char r, char g, char b);

/**
 * draw an image to the screen by its location
 * @returns 0 on success, nonzero on failure
 */
int draw_image(const struct image *img);

/**
 * called at the end of each frame to swap buffers, present the drawing etc
 * @returns 0 on success, nonzero on failure
 */
int draw_frame_end();

/**
 * allocate/initialize memory for textures
 * @param n maximum number of textures that can be loaded at any time
 * @returns 0 on success, nonzero on failure
 */
int init_texture_memory(size_t n);

/**
 * load a texture from a file name, and associate it with a reference string
 * @param fname the path to the texture file
 * @param ref the key we use to get the texture in texture_get_by_name()
 * @returns 0 on success, nonzero on failure
 */
int texture_load(char *fname, const char *ref);

/**
 * get a texture we have loaded by name
 *
 * note we do not know what kind of texture this is. that is to be determined
 * on an implementation-by-implementation basis. eg for SDL2 this is a pointer
 * to an SDL_Texture, but on PS2 this is a GSTEXTURE!
 *
 * @param ref the name we have associated with the texture
 * @returns a pointer on success, or 0/NULL on failure
 */
void *texture_get_by_name(const char *ref);


#endif
