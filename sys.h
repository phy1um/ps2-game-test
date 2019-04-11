/**
 * definition of system functionality
 */
#ifndef SYS_H__
#define SYS_H__

/**
 * first thing that should be called in main
 * @returns 0 on success, else nonzero
 */
int sys_init();

/**
 * cleanup and shutdown systems (not critical on playstation 2)
 * @returns 0 on success, else nonzero (eg it is not safe to terminate)
 */
int sys_shutdown();

/**
 * sleep the current execution
 * @param ms how long to sleep for in milliseconds
 */
void sys_sleep(unsigned long ms);

/**
 * get the current time in milliseconds
 *
 * not guaraneed to be any specific value (usually ms since program start)
 * but it IS valid for differences
 * @returns the time in milliseconds
 */
unsigned long sys_time_ms();

#endif
