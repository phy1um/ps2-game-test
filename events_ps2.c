
#include "events.h"
#include "platform.h"
#include <libpad.h>
#include <kernel.h>

static char pad_buffer[256] __attribute__((aligned(64)));
char pad_read_space[32];

#define R_SIO2MAN "rom0:SIO2MAN"
#define R_PADMAN "rom0:PADMAN"

int pad_wait(int port, int slot, int tries)
{
    int now;
    int prev = -1;
    now = padGetState(port, slot);
    if(now == PAD_STATE_DISCONN) {
        info("Pad disconnected");
        return -1;
    }

    while((now != PAD_STATE_STABLE) && (now != PAD_STATE_FINDCTP1)) {
        prev = now;
        now = padGetState(port, slot);
        tries--;
        if(tries == 0) {
            info("Failed to get state from pad");
            break;
        }
    }

    return 0;
}

/**
 * Hard coded to a single pad for now
 */
void events_init()
{
    int rc = SifLoadModule(R_SIO2MAN, 0, 0);
    if(rc < 0) {
        fatal("Failed to load SIO2MAN sif");
        return;
    }

    rc = SifLoadModule(R_PADMAN, 0, 0);
    if(rc < 0) {
        fatal("Failed to load PADMAN sif");
        return;
    }

    rc = padInit(0);
    if(rc < 0) {
        fatal("Failed to init pad");
        return;
    }

    rc = padPortOpen(0, 0, &pad_buffer);
    if(rc < 0) {
        fatal("Failed to open pad 0:0");
    }


}

static int prev_inputs;
void handle_events()
{
    if(pad_wait(0, 0, 10) < 0) {
        error("Failed to get info from pad 0:0");
        return;
    }

    int rc = padRead(0, 0, (struct padButtonStatus *) &pad_read_space);
    struct padButtonStatus *pad_mem = &pad_read_space;
    if(rc != 0) {
        int pad = 0xffff ^ pad_mem->btns;
        int changed = pad ^ prev_inputs;
        prev_inputs = pad;

        if(changed & PAD_LEFT) {
           handler(EV_LEFT);
        }
        if(changed & PAD_RIGHT) {
            handler(EV_RIGHT);
        }
        if(changed & PAD_DOWN) {
            handler(EV_DOWN);
        }
        if(changed & PAD_UP) {
            handler(EV_UP);
        }
        if(changed & PAD_CIRCLE) {
            handler(EV_0);
        }
        if(changed & PAD_CROSS) {
            handler(EV_1);
        }
        if(changed & PAD_SQUARE) {
            handler(EV_2);
        }
        if(changed & PAD_TRIANGLE) {
            handler(EV_3);
        }
        if(changed & PAD_START) {
            handler(EV_START);
        }
        if(changed & PAD_SELECT) {
            handler(EV_SELECT);
        }
    }

    return;
}
