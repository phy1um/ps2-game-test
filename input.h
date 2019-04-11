/**
 * system to manage button state from dumb hardware-based events
 *
 * @author phy1um
 * @date 2019-03-20
 */
#ifndef PS2_GAME_INPUT_H
#define PS2_GAME_INPUT_H

/**
 * reset tracking for buttons that were pressed or released in a frame
 */
void input_frame_begin();

/**
 * initialise this input manager, install it to the events system
 */
void input_init();

/**
 * test if a button is being held in this frame
 * @param b button identifier of the form EV_X
 * @returns 1 if held else 0
 */
int input_held(int b);

/**
 * test if a button was pressed down in this frame
 * @param b button identifier of the form EV_X
 * @returns 1 if pressed else 0
 */
int input_pressed(int b);

/**
 * test if a button was released in this frame
 * @param b button identifier of the form EV_X
 * @returns 1 if released else 0
 */
int input_release(int b);

#endif
