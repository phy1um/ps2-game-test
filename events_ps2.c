/**
 * even poller for playstation 2, handles pad input
 *
 * @author phy1um
 * @date 2019-04-01
 */
#include "events.h"
#include "platform.h"
#include <libpad.h>
#include <kernel.h>

// create space for pad data storage
static char pad_buffer[256] __attribute__((aligned(64)));
// button states
char pad_read_space[32];

// define IO modules
#define R_SIO2MAN "rom0:SIO2MAN"
#define R_PADMAN "rom0:PADMAN"

/**
 * wait for pad to be in ready state
 * 
 * based on code from ps2dev examples
 *
 * @param port which controller port to look at
 * @param slot which slot within the port to loko at (0 if no multitap)
 * @param tries how many attempts to make communicating with pad
 */
int pad_wait(int port, int slot, int tries)
{
    int now;
    int prev = -1;
    // if the pad is disconnected don't bother waiting
    now = padGetState(port, slot);
    if(now == PAD_STATE_DISCONN) {
        info("Pad disconnected");
        return -1;
    }
    
    // keep polling while the pad isn't ready
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
 * initialise modules to talk to a controller
 *
 * hard coded to a single pad for now
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
/**
 * get input events from the controller and pass them to handler
 */
void handle_events()
{
    // make sure the pad is ready
    if(pad_wait(0, 0, 10) < 0) {
        error("Failed to get info from pad 0:0");
        return;
    }
    // read button state into memory
    int rc = padRead(0, 0, (struct padButtonStatus *) &pad_read_space);
    struct padButtonStatus *pad_mem = &pad_read_space;
    if(rc != 0) {
        // get the difference from the previous state
        int pad = 0xffff ^ pad_mem->btns;
        int changed = pad ^ prev_inputs;
        prev_inputs = pad;

        // decode bitmask and handle individual buttons
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
