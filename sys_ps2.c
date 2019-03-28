
#include <romfs_io.h>
#include <gsToolkit.h>
#include <kernel.h>
#include <time.h>
#include "sys.h"
#include "video.h"
#include "platform.h"

GSGLOBAL *gsGlobal;
GSFONTM *gsFontm;

int main_thread_id;
int watcher_id;

void wakeup_target(s32 alarm_id, u16 time, void *arg)
{
    int tgt = *((int*)arg);
    WakeupThread(tgt);
}

void sys_sleep(unsigned long ms)
{
#if 0
    u16 ticks = (u16) ms;
    SetAlarm(ticks, &wakeup_target, (void*)&main_thread_id);
    printf("Going to sleep...");
    SleepThread();
    printf("Woke up!");
#else
    clock_t start = clock();
    clock_t now;
    float diff = 0;
    do {
        now = clock();
        diff = (float) (now - start) / (float) CLOCKS_PER_SEC;
    }
    while(diff*1000 < ms);
#endif
}

int sys_init()
{
    rioInit();
    if(gsGlobal != 0) {
        fatal("The global GS state was already initialised");
        return -1;
    }

    gsGlobal = gsKit_init_global();
    gsFontm = gsKit_init_fontm();
#if VIDEO_HEIGHT == 480
    gsGlobal->Mode = GS_MODE_DTV_480P;
#elif VIDEO_HEIGHT == 720
    gsGlobal->Mode = GS_MODE_DTV_720P;
#else
    #error "Unsupported video height defined"
#endif
    gsGlobal->Interlace = GS_NONINTERLACED;
    gsGlobal->Field = GS_FRAME;
    gsGlobal->Width = VIDEO_WIDTH;
    gsGlobal->Height = VIDEO_HEIGHT;
    gsGlobal->PSM = GS_PSM_CT24;
    gsGlobal->PSMZ = GS_PSMZ_16S;
    gsGlobal->DoubleBuffering = GS_SETTING_ON;
    gsGlobal->ZBuffering = GS_SETTING_OFF;

    dmaKit_init(D_CTRL_RELE_OFF, D_CTRL_MFD_OFF, D_CTRL_STS_UNSPEC,
            D_CTRL_STD_OFF, D_CTRL_RCYC_8, 1 << DMA_CHANNEL_GIF);
    // init dmac
    dmaKit_chan_init(DMA_CHANNEL_GIF);
    gsKit_init_screen(gsGlobal);
    gsKit_fontm_upload(gsGlobal, gsFontm);

    main_thread_id = GetThreadId();

    return 0;
}

int sys_shutdown()
{
    SleepThread();
    return 0;
}

unsigned long sys_time_ms()
{
    return (clock()*1000)/CLOCKS_PER_SEC;
}

