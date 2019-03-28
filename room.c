
#include "room.h"
#include "platform.h"

#define ROOM_MAX 5

#define testid(i) do {\
    if((i) < 0 || (i) >= room_head) {fatal("Changed to invalid room ID");} \
}while(0)

static int room_in = 0;
static int room_head = 0;
static struct room *rooms[ROOM_MAX];

int room_bind(struct room *r)
{
    if(room_head >= ROOM_MAX) {
        fatal("Over-bound rooms - too many!");
        return -1;
    }
    rooms[room_head] = r;
    int ret = room_head;
    room_head += 1;
    return ret;
}

int room_load(int id)
{
    testid(id);
    rooms[id]->load();
    return 0;
}

int room_unload(int id)
{
    testid(id);
    rooms[id]->unload();
    return 0;
}

int room_enter(int id)
{
    testid(id);
    room_in = id;
    rooms[id]->enter();
    return 0;
}

int room_tick()
{
    testid(room_in);
    rooms[room_in]->tick();
    return 0;
}

int room_draw()
{
    testid(room_in);
    rooms[room_in]->draw();
    return 0;
}
