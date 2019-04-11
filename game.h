/**
 * definitions of core game functions driving the flow, and menu displays
 *
 * @author phy1um
 * @date 2019-03-20
 */
#ifndef GAME_H__
#define GAME_H__

#include "menu.h"

/**
 * called once to setup the memory and state for the game
 * @returns 0 on success, else nonzero
 */
int game_enter();

/**
 * run the main game loop until it terminates
 * @returns 0 on success, else nonzero
 */
int game_loop();

/**
 * bind a new menu to be displayed by this game
 * @returns 0 on success, else nonzero
 */
int game_set_menu(struct menu *m);

/**
 * display currently bound menu
 * @returns 0 on success, else nonzero
 */
int game_menu_on();

/**
 * hide currently bound menu
 * @returns 0 on success, else nonzero
 */
int game_menu_off();

#endif
