#ifndef GAME_H__
#define GAME_H__

#include "menu.h"

int game_enter();
int game_loop();

int game_set_menu(struct menu *m);
int game_menu_on();
int game_menu_off();

#endif
