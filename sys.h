#ifndef SYS_H__
#define SYS_H__

int sys_init();
int sys_shutdown();
void sys_sleep(unsigned long ms);

unsigned long sys_time_ms();

#endif
