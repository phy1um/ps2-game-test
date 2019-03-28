
#include "input.h"
#include "events.h"
#include "draw.h"
#include "room.h"
#include "menu.h"
#include "game.h"
#include "platform.h"

#define sgn(z) ( ( (z) > 0) - ( (z) < 0) )

#define SPEED 1.8f

static struct sprite player = {
    0, 0, 0, 20, 20, 20, 20, 0, 0 };
static struct image im = {&player, 0, 0, 1.3f};

static struct menu menu = {
    0,0,5,1,1,0
};

static float x = 50;
static float y = 50;
void tick()
{
    float dx = 0;
    float dy = 0;
    if(input_held(EV_UP)) {
        dy -= SPEED;
    }
    else if(input_held(EV_DOWN)) {
        dy += SPEED;
    }
    if(input_held(EV_LEFT)) {
        dx -= SPEED;
    }
    else if(input_held(EV_RIGHT)) {
        dx += SPEED;
    }

    if(dx != 0 && dy != 0) {
        dx *= 0.707;
        dy *= 0.707;
    }

    x += dx;
    y += dy;
    if(input_pressed(EV_START)) {
        game_menu_on();
    }
}

void draw()
{
    im.x = x;
    im.y = y;
    draw_image(&im);
}

void menu_action() {
    x = 50;
    y = 50;
}

void load()
{
    void *p = texture_get_by_name("tiles");
    if(p == 0) {
        int rc = texture_load("host:res/tiles.png", "tiles");
        if(rc != 0) {
            fatal("Failed to load tiles.png!");
            return;
        }
    }
    p = texture_get_by_name("tiles");
    if(p == 0) {
        fatal("Failed to load texture on entering room SANDBOX");
        return;
    }
    player.texture = p;

    menu.options = malloc(20*5);
    menu.actions = malloc(5*sizeof(action_t));
    menu.options[0] = "Option 1";
    menu.options[1] = "Option 2";
    menu.options[2] = "Option 3";
    menu.options[3] = "Option 4";
    menu.options[4] = "Reset Position";

    menu.actions[4] = &menu_action;

    game_set_menu(&menu);
}

void unload()
{

}

void enter()
{

}

static struct room sandbox_room = {
    &tick, &draw, &load, &unload, &enter, 0
};

struct room *get_sandbox_room()
{
    return &sandbox_room;
}
