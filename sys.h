#ifndef SYS_H__
#define SYS_H__

int sys_init();
int sys_shutdown();
void sys_sleep(long ms);
long sys_time_ms();

#endif
