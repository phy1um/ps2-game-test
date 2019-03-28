#ifndef PS2_GAME_MENU_H__
#define PS2_GAME_MENU_H__

#include <stdlib.h>

typedef void(*action_t)(); 

struct menu {
    char **options;
    action_t *actions;
    size_t entry_count;
    int pause_ticks;
    int draw_over;
    void(*draw)();
};

#endif
