#ifndef PS2_DRAW_H__
#define PS2_DRAW_H__

#include <stdlib.h>

struct sprite {
    void *texture;
    float u1;
    float v1;
    float u2;
    float v2;
    float w;
    float h;
    float offset_x;
    float offset_y;
};

struct image {
    struct sprite *tgt;
    float x;
    float y;
    float scale;
};

int draw_frame_start();
int draw_string(const char *str, float x, float y, float scale, 
        char r, char g, char b);
int draw_image(const struct image *img);
int draw_frame_end();

int init_texture_memory(size_t n);
int texture_load(char *fname, const char *ref);
void *texture_get_by_name(const char *ref);


#endif
