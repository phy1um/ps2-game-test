
#include <SDL.h>
#include <stdlib.h>
#include <stdio.h>

FILE *LOGFILE;

int sys_init()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    LOGFILE = fopen("run.log", "w");
    return 0;
}

int sys_shutdown()
{
    SDL_Quit();
    exit(0);
    return 0;
}

void sys_sleep(unsigned long ms)
{
    SDL_Delay(ms);
}

unsigned long sys_time_ms()
{
    return SDL_GetTicks();
}
