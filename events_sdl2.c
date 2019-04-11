/**
 * SDL2 implementation of event and inout logic
 *
 * @author phy1um
 * @date 2019-04-10
 */
#include "events.h"
#include "platform.h"

#include <SDL.h>

// no setup needed, SDL_Init handles this
void events_init() {}

/**
 * use default SDL handlers for events, and pass key events to the handler
 */
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
