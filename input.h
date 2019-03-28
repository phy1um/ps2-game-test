#ifndef PS2_GAME_INPUT_H
#define PS2_GAME_INPUT_H

void input_frame_begin();
void input_init();

int input_held(int b);
int input_pressed(int b);
int input_release(int b);

#endif
