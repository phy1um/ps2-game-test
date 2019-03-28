
#include "events.h"
#include "platform.h"

#include <SDL.h>


void events_init() {}

void handle_events()
{
    SDL_Event ev = {0};
    while(SDL_PollEvent(&ev)) {
        if(ev.type == SDL_KEYDOWN || ev.type == SDL_KEYUP) {
            switch(ev.key.keysym.sym) {
                case SDLK_w:
                    handler(EV_UP);
                    break;
                case SDLK_a:
                    handler(EV_LEFT);
                    break;
                case SDLK_s:
                    handler(EV_DOWN);
                    break;
                case SDLK_d:
                    handler(EV_RIGHT);
                    break;
                default:
                    continue;
            }
        }
    }
}
