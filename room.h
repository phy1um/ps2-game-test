#ifndef ROOM_HEADER__
#define ROOM_HEADER__

struct room {
    void(*tick)();
    void(*draw)();
    void(*load)();
    void(*unload)();
    void(*enter)();
    int loaded;
};


int room_bind(struct room *r);
int room_load(int id);
int room_unload(int id);
int room_enter(int id);

int room_tick();
int room_draw();


#endif
